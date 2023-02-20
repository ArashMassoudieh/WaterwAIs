
#ifndef LAYERPOLYGONITEM_H_4D75995A8124A968B62B
#define LAYERPOLYGONITEM_H_4D75995A8124A968B62B

#include "LayerGraphicsItem.h"
#include <QColor>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// PolygonLayerItem

class PolygonLayerItem: public LayerPolyItem {
public:
    PolygonLayerItem(const LayerGraphicsSettings& gsettings,
        const QPolygonF& polygon, bool randomize_color = false);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget*) override;
private:
    void setColors();
    
    bool randomize_color_ = false;

    QColor color_;
    QColor base_color_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // LAYERPOLYGONITEM_H_4D75995A8124A968B62B
