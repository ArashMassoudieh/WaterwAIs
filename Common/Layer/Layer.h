
#ifndef LAYER_H_9DB6E72CAD45
#define LAYER_H_9DB6E72CAD45

#include <QRectF>
#include <QColor>
#include <QPen>

#include "LayerModel.h"
#include "LayerGraphicsItem.h"

namespace WaterWays {

class LayerSceneInterface;

///////////////////////////////////////////////////////////////////////////
// Layer

class Layer: public QObject, public LayerGraphicsItems {
    Q_OBJECT

public:
    enum Option {
        None        = 0x0,
        UsesShapes  = 0x1,
        FixedZValue = 0x2,
    };
    Q_DECLARE_FLAGS(Options, Option)

    using Ptr           = std::shared_ptr<Layer>;
    using LayerModelPtr = std::shared_ptr<LayerModel>;
    using GraphicsItems = std::vector<QGraphicsItem*>;

    Layer(LayerSceneInterface* scene = nullptr, LayerModelPtr model = {},
        const QColor& color = Qt::black, Options options = Option::None);

    ~Layer() override;

    void clear();

    // Builds underlying layer model from JSON URL and add layer to the scene.
    void getFromJson(QStringView json_url);

    // Model
    void setModel(LayerModelPtr model) { model_ = model; }
    LayerModelPtr model() { return model_; }   

    // Name
    QString name() const { return model_ ? model_->name() : ""; }

    // Icon
    const QPixmap& icon() const 
        { return model_ ? model_->icon() : empty_icon_; }

    // Graphics items
    const GraphicsItems& getItems() { return items_; }

    // Color
    virtual void setColor(const QColor& c);
    QColor color() const { return color_; }

    // Graphics settings
    const LayerGraphicsSettings& settings() const { return gsettings_; }
    void setSettings(const LayerGraphicsSettings& gsettings);    

    // Visible
    bool visible() const { return visible_; }
    void setVisible(bool val);

    // Opacity
    qreal opacity() const { return opacity_; }
    void setOpacity(qreal val);

    // Line type
    void setLineType(Qt::PenStyle style);

    // Line width
    void setLineWidth(int width);

    // Z-value
    int zValue() const { return z_value_; }
    bool setZValue(int z);

    // Returns pointer to model class if the model was derived from it.
    template<typename T> T* to_model() {
        T* model = nullptr;
        if (model_)
            model = qobject_cast<T*>(model_.get());
        return model;
    }    

signals:
    void layerReady();

protected slots:
    void onModelLoaded();

protected:
    // LayerGraphicsItems
    void addItem(QGraphicsItem* item) override;
    
    void settingsChanged();

    // Prepares graphic settings before passing them to layer graphic items.
    virtual void prepareSettings();

    // Builds and adds graphic items from the layer model.
    virtual void addItemsFromModel();

    QPixmap empty_icon_;
    LayerGraphicsSettings gsettings_;
    

    LayerSceneInterface* scene_ = nullptr;
    LayerModelPtr model_;    
    GraphicsItems items_;

    bool  visible_ = true;
    qreal opacity_ = 1;
    int   z_value_ = 0;

    QColor color_;
    QRectF bound_rect_;

    Options options_;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Layer::Options)

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // LAYER_H_9DB6E72CAD45
