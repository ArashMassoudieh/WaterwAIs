#ifndef LAYERNODEITEM_H_A441F580D6914705
#define LAYERNODEITEM_H_A441F580D6914705

#include "MetaLayerItem.h"
#include "MetaLayerModelItem.h"

namespace WaterWays {

class MetaComponentItem;

//////////////////////////////////////////////////////////////////////////
// NodeLayerItem
//
// This class represents a Node graphics item in the MetaModel layer.

class NodeLayerItem: public MetaLayerItem {
public:
    using NodeItem = MetaLayerModelItems::NodeItem;

    NodeLayerItem(const LayerGraphicsSettings& gsettings, NodeItem& node_item);
    ~NodeLayerItem() override;
    
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    // Coordinates
    void setCoordinates(const QPointF coordinates) 
        { coordinates_ = coordinates; }

    const QPointF& coordinates() const { return coordinates_; }

    // Size
    void setSize(const QSizeF& size);
    const QSizeF& size() const { return size_; }

    qreal getX() const { return coordinates_.x(); }
    qreal getY() const { return coordinates_.y(); }

    QPointF origin() const { return {getX(), getY()}; }

    qreal width() const  { return size_.width();}
    qreal height() const { return size_.height(); }

private:
    QPointF   coordinates_;
    QSizeF    size_;
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // LAYERNODEITEM_H_A441F580D6914705
