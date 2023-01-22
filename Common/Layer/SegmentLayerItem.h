

#ifndef SEGMENTLAYERITEM_H_A453AAE93740D71A
#define SEGMENTLAYERITEM_H_A453AAE93740D71A

#include "LayerGraphicsItem.h"
#include <vector>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// SegmentLayerItem

class SegmentLayerItem: public LayerLineItem {
public:
    SegmentLayerItem(const LayerGraphicsSettings& gsettings,
        const QPointF& s_point, const QPointF& e_point);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget*) override;

protected:
    void onItemMove(const QPointF& pos) override;

private:
    QPointF start_point_;
    QPointF end_point_;

    std::vector<QPointF> points_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // SEGMENTLAYERITEM_H_A453AAE93740D71A
