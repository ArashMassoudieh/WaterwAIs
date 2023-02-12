
#include "MapScene.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

namespace WaterwAIs {

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

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mousePressEvent(event);

    // When we entered the panning drag mode, we still allow graphic
    // items to be selected, but we need clear the acceptance of the event
    // after item selection in order to let the GraphicView to do panning.
    if (drag_mode_)
        event->setAccepted(false);    
}

} // namespace WaterwAIs