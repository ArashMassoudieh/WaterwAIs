#ifndef LAYERSCENEINTERFACE_H_987CD0B94018CD8F
#define LAYERSCENEINTERFACE_H_987CD0B94018CD8F

#include <QRectF>
#include <vector>

class QGraphicsItem;

namespace WaterwAIs {

class LayerSceneInterface {
public:
    using GraphicsItems = std::vector<QGraphicsItem*>;

    // Add layer item to the scene, allowing to specify layer's bounding
    // rectangle.
    virtual void addLayerItem(QGraphicsItem* /*item*/,
        const QRectF& bound_rect = QRectF{}) = 0;

    // Notification when layer visual settings changed.
    // Layer bounding rectangle may be passed.
    virtual void onLayerChanged(const QRectF& bound_rect = QRectF{}) = 0;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // LAYERSCENEINTERFACE_H_987CD0B94018CD8F
