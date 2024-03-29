
#include "MetaLayerItem.h"

namespace WaterwAIs {

namespace {
// Default Node parameters
static constexpr auto   data_key = 1000;
static constexpr auto   item_string = "MLItem";

} // anonymous

//////////////////////////////////////////////////////////////////////////
// MetaLayerItem

MetaLayerItem::MetaLayerItem(const LayerGraphicsSettings& gsettings,
    ModelItem& model_item)
    : LayerGenericItem{gsettings}, model_item_{model_item} {

    // Allow item to be selected.
    LayerGenericItem::setFlags(QGraphicsItem::ItemIsSelectable);

    // Common settings
    setData(data_key, item_string);

    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);

    // z-Value
    setZValue(item_zvalue);

    // Tooltip
    setAcceptHoverEvents(true);
}

MetaLayerItem* MetaLayerItem::item_cast(QGraphicsItem* item) {
    if (item && item->data(data_key).toString() == item_string)
        return static_cast<MetaLayerItem*>(item);
    return {};
}

void MetaLayerItem::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/) {
    if (toolTip().isEmpty())
        setToolTip(model_item_.toolTip());
}

} // namespace WaterwAIs