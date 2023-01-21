
#include "SegmentLayerItem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// SegmentLayerItem

SegmentLayerItem::SegmentLayerItem(const LayerGraphicsSettings& gsettings,
    const QPointF& s_point, const QPointF& e_point)
    : LayerLineItem{gsettings}, start_point_{s_point}, end_point_{e_point} {

    setLine(QLineF{start_point_, end_point_});

    //setZValue((x + y) % 2);
}

QRectF SegmentLayerItem::boundingRect() const {
    /*auto dx = end_point_.x() - start_point_.x();
    auto dy = end_point_.y() - start_point_.y();
    return QRectF(start_point_.x(), start_point_.y(), dx, dy);*/

    return LayerLineItem::boundingRect();
}

QPainterPath SegmentLayerItem::shape() const {
    /*QPainterPath path;
    path.addRect(boundingRect());
    return path;*/

    return LayerLineItem::shape();
}

void SegmentLayerItem::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget*) {
    onPaint(painter, option);

    painter->drawLine(line());

    //painter->drawLine(start_point_.x(), start_point_.y(), end_point_.x(),
    //    end_point_.y());
}

void SegmentLayerItem::onItemMove(const QPointF& pos) {
    points_.emplace_back(pos);
}

} // namespace WaterWays