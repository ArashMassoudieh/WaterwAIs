
#ifndef LAYERLINKITEM_H_B82CFCE549CBCE96
#define LAYERLINKITEM_H_B82CFCE549CBCE96

#include "MetaLayerItem.h"
#include "MetaLayerModelItem.h"

namespace WaterWays {

class NodeLayerItem;

//////////////////////////////////////////////////////////////////////////
// LinkLayerItem
// 
// This class represents a Link graphics item in the MetaModel layer
// which connects two Node graphics items.

class LinkLayerItem: public MetaLayerItem {
public:
    using LinkItem = MetaLayerModelItems::LinkItem;

    LinkLayerItem(const LayerGraphicsSettings& gsettings, LinkItem& link_item,
        const NodeLayerItem* src_node, const NodeLayerItem* dest_node);    
    
    // Source
    void setSourceNode(const NodeLayerItem* node) { source_node_ = node; }
    const NodeLayerItem* sourceNode() const { return source_node_; }

    // Destination
    void setDestinationNode(const NodeLayerItem* node) { dest_node_ = node; }
    const NodeLayerItem* destinatioNode() const { return dest_node_; }

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    QPainterPath shape() const override;

    void adjust();
private:
    const NodeLayerItem* source_node_;
    const NodeLayerItem* dest_node_;

    QPointF        source_point_;
    QPointF        dest_point_;

    qreal          arrow_size_;
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // LAYERLINKITEM_H_B82CFCE549CBCE96
