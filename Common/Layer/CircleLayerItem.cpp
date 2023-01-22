
#include "CircleLayerItem.h"
#include <QDebug>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// CircleLayerItem

CircleLayerItem::CircleLayerItem(const LayerGraphicsSettings& gsettings,
    const QPoint& center, qreal radius)
    : LayerGraphicsItem{gsettings}, center_{center}, radius_{radius} {
}

QRectF CircleLayerItem::boundingRect() const {
    return QRectF(center_.x() - radius_, center_.y() - radius_,
        radius_ * 2, radius_ * 2);
}

QPainterPath CircleLayerItem::shape() const {
    auto path = QPainterPath{};

    path.addEllipse(boundingRect());
    return path;
}

void CircleLayerItem::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget*) {
    onPaint(painter, option);
    
    //qDebug() << "center=" << center_ << ", radius=" << radius_;

    painter->drawEllipse(center_.x() - radius_, center_.y() - radius_,
        radius_ * 2, radius_ * 2);
}

} // namespace WaterwAIs
