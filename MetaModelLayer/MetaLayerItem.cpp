
#include "MetaLayerItem.h"

namespace WaterWays {

namespace {
// Default Node parameters
static constexpr auto   data_key = 1000;
static constexpr auto   item_string = "MLItem";
static constexpr double item_zvalue = 40000;

} // anonymous

//////////////////////////////////////////////////////////////////////////
// MetaLayerItem

MetaLayerItem::MetaLayerItem(const LayerGraphicsSettings& gsettings,
    ModelItem& model_item)
    : LayerGenericItem{gsettings}, model_item_{model_item} {
    // Common settings
    setData(data_key, item_string);

    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);

    setZValue(item_zvalue);
}

MetaLayerItem* MetaLayerItem::item_cast(QGraphicsItem* item) {
    if (item && item->data(data_key).toString() == item_string)
        return static_cast<MetaLayerItem*>(item);
    return {};
}

} // namespace WaterWays