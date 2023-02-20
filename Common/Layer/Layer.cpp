
#include "Layer.h"
#include "LayerSceneInterface.h"

namespace WaterwAIs {

///////////////////////////////////////////////////////////////////////////
// Layer

Layer::Layer(LayerSceneInterface* scene, LayerModelPtr model,
    QStringView name, const QColor& color, Options options,
    QStringView description)
    : scene_{scene}, model_{model}, name_{name.toString()}, color_{color}
    , options_{options}, description_{description.toString()} {
    
    gsettings_.pen.setStyle(Qt::SolidLine);

    // For "contour" layers let's use a wider pen width by default.
    if (!options_.testFlag(Option::UsesShapes))
        gsettings_.pen.setWidth(3);
}

Layer::~Layer() {
    clear();
}

void Layer::clear() {
    items_.clear();
    bound_rect_ = {};
}

QString Layer::name() const {
    auto name = model_ ? model_->name() : QString{};
    return name.isEmpty() ? name_ : name;
}

void Layer::getFromJson(QStringView json_url) {
    if (model_) {
        connect(model_.get(), &LayerModel::modelLoaded, this,
            [this](auto result) { onModelLoaded(result); });

        model_->getFromJson(json_url);
    }    
}

void Layer::onModelLoaded(bool result) {
    if (result) {
        clear();

        // Adding graphic items from the model.
        addItemsFromModel();
    } else {
        qDebug() << "Model loading failed";
    }
    
    emit layerReady(result);
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

QString Layer::displayText() const {    
    auto text = name();

    if (model_->downloading())
        text += " - downloading...";
    else if (model_->downloadFailed())
        text += " - [failed]";

    return text;
}


} // namespace WaterwAIs