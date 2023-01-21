
#include "MapScene.h"
#include <QGraphicsItem>

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// MapScene

MapScene::MapScene(QObject* qwidget)
    :QGraphicsScene(qwidget) {
}

void MapScene::addLayerItem(QGraphicsItem* item, const QRectF& bound_rect) {
    addItem(item);

    // If caller provided item's bounding rectangle, let's use it.
    if (bound_rect.isValid())
        rect_ |= bound_rect;
    else
        rect_ |= item->boundingRect();
}

void MapScene::onLayerChanged(const QRectF& bound_rect) {
    update(bound_rect);
}

} // namespace WaterWays