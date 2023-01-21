
#include "Layer.h"
#include "LayerSceneInterface.h"

namespace WaterWays {

///////////////////////////////////////////////////////////////////////////
// Layer

Layer::Layer(LayerSceneInterface* scene, LayerModelPtr model,
    const QColor& color, Options options)
    : scene_{scene}, model_{model}, color_{color}, options_{options} {
    
    gsettings_.pen.setStyle(Qt::SolidLine);
}

Layer::~Layer() {
    clear();
}

void Layer::clear() {
    items_.clear();
    bound_rect_ = {};
}

void Layer::getFromJson(QStringView json_url) {
    if (model_) {
        connect(model_.get(), &LayerModel::modelLoaded, this,
            [this]() { onModelLoaded(); });

        model_->getFromJson(json_url);
    }    
}

void Layer::onModelLoaded() {
    if (!model_) {
        qDebug() << "Model loaded without model object!";
        Q_ASSERT(false);
        return;
    }

    clear();

    // Adding graphic items from the model.
    addItemsFromModel();
    
    emit layerReady();
}

void Layer::addItemsFromModel() {
    // Allows derived classes to prepare graphics settings before passing
    // them to layer graphics items.
    prepareSettings();

    // Base implementation just asks the model to provide graphic presentation
    // of its items.
    // 
    // Derived classes may provide a different way to build presentation layer
    // from the model items.
    model_->addGraphicsItems(gsettings_, *this);
}

void Layer::addItem(QGraphicsItem* item) {
    if (!item)
        return;

    if (scene_) {
        items_.emplace_back(item);

        // Setting layer's zValue
        item->setZValue(z_value_);

        auto item_rc = item->boundingRect();

        // Adding item to the scene.
        scene_->addLayerItem(item, item_rc);

        // Updating bound rectangle from the item.
        bound_rect_ |= item_rc;
    } else {
        // Delete the item if we can't pass ownership to the scene.
        delete item;
    }
}

void Layer::setSettings(const LayerGraphicsSettings& gsettings) {
    gsettings_ = gsettings;
    settingsChanged();
}

void Layer::setColor(const QColor& c) {
    color_ = c;
    prepareSettings();
    settingsChanged();
}

void Layer::prepareSettings() {
    // By default, set color for either brush or pen, depending on whether
    // the layer uses shapes or lines
    if (options_.testFlag(Option::UsesShapes))
        gsettings_.brush.setColor(color_);
    else
        gsettings_.pen.setColor(color_);
}

void Layer::setVisible(bool val) {
    visible_ = val;

    for (auto item : items_)
        item->setVisible(visible_);

    settingsChanged();
}

void Layer::setOpacity(qreal val) {
    opacity_ = val;

    for (auto item : items_)
        item->setOpacity(opacity_);

    settingsChanged();
}

void Layer::setLineType(Qt::PenStyle style) {
    gsettings_.pen.setStyle(style);
    settingsChanged();
}

// Line width
void Layer::setLineWidth(int width) {
    gsettings_.pen.setWidth(width);
    settingsChanged();
}

bool Layer::setZValue(int z) {
    if (options_.testFlag(Option::FixedZValue))
        return false; // the layer has a fixed z-order

    z_value_ = z;

    for (auto item : items_)
        item->setZValue(z_value_);

    settingsChanged();
    return true;
}

void Layer::settingsChanged() {
    if (scene_)
        scene_->onLayerChanged(bound_rect_);
}

} // namespace WaterWays