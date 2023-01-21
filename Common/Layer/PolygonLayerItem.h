
#ifndef LAYERPOLYGONITEM_H_4D75995A8124A968B62B
#define LAYERPOLYGONITEM_H_4D75995A8124A968B62B

#include "LayerGraphicsItem.h"

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// PolygonLayerItem

class PolygonLayerItem: public LayerPolyItem {
public:
    PolygonLayerItem(const LayerGraphicsSettings& gsettings,
        const QPolygonF& polygon);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget*) override;
private:
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // LAYERPOLYGONITEM_H_4D75995A8124A968B62B
