
#include "PolygonLayerItem.h"

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// PolygonLayerItem

PolygonLayerItem::PolygonLayerItem(const LayerGraphicsSettings& gsettings,
    const QPolygonF& polygon) : LayerPolyItem{gsettings} {
    setPolygon(polygon);
}

void PolygonLayerItem::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget*) {
    onPaint(painter, option);
    
    setPen  (painter->pen());
    setBrush(painter->brush());
    LayerPolyItem::paint(painter, option);
}

} // namespace WaterWays