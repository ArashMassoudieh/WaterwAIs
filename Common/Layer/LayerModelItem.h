#ifndef LAYERMODELITEM_H_9B0DEA13FDC912E0
#define LAYERMODELITEM_H_9B0DEA13FDC912E0

#include <QJsonValue>
#include <QGraphicsItem>

namespace WaterWays {

class LayerGraphicsSettings;

//////////////////////////////////////////////////////////////////////////
// LayerGraphicsItems

class LayerGraphicsItems {
public:
    virtual ~LayerGraphicsItems() {}

    // This function adds a graphics item to the collection.
    virtual void addItem(QGraphicsItem*) = 0;
};

//////////////////////////////////////////////////////////////////////////
// LayerModelItem
// 
// An abstract class that represents an item for the layer model.

class LayerModelItem {
public:
    virtual ~LayerModelItem() {}

    using GraphicsItems = std::vector<QGraphicsItem*>;

    // Fills the layer item from the JSON value
    virtual void getFromJson(const QJsonValue& json_value) = 0;

    // Allows the layer item to provide graphics items for presentation.
    // The function provides caller's "graphics settings" with color and other
    // attributes, which may be applied to the item's graphics items.
    virtual void addGraphicsItems(const LayerGraphicsSettings& /*gsettings*/,
        LayerGraphicsItems& /*items*/) = 0;
};

} // namespace WaterWays


//////////////////////////////////////////////////////////////////////////
#endif //LAYERMODELITEM_H_9B0DEA13FDC912E0
