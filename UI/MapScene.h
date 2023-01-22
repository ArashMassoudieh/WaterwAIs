#ifndef MAPSCENE_H_850176E6CC75
#define MAPSCENE_H_850176E6CC75

#include <QGraphicsScene>
#include <Layer/LayerSceneInterface.h>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MapScene

class MapScene: public QGraphicsScene, public LayerSceneInterface {
    Q_OBJECT
public:
    using GraphicsItems = std::vector<QGraphicsItem*>;

    MapScene(QObject* qwidget = nullptr);

    // LayerSceneInterface
    void addLayerItem(QGraphicsItem* item, 
        const QRectF& bound_rect = QRectF{}) override;

    void onLayerChanged
        (const QRectF& bound_rect = QRectF{}) override;

    QRectF boundingRect() const { return rect_; }

private:
    QRectF rect_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MAPSCENE_H_850176E6CC75
