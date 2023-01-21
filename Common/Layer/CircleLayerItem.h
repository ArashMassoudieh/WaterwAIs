
#ifndef CIRCLELAYERITEM_H_AD619BE899F15CEA
#define CIRCLELAYERITEM_H_AD619BE899F15CEA

#include "LayerGraphicsItem.h"

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// CircleLayerItem

class CircleLayerItem: public LayerGenericItem {
public:
    CircleLayerItem(const LayerGraphicsSettings& gsettings,
        const QPoint& center, qreal radius);

    QPoint center() const { return center_; }
    qreal  raduis() const { return radius_; }

    // Graphics item overrides
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget*) override;

private:
    QPoint center_;
    qreal  radius_;
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // CIRCLELAYERITEM_H_AD619BE899F15CEA
