#include <QDebug>
#include <QMouseEvent>
#include <QPen>
#include <QColor>

#include "graphicsview.h"
#include "mapscene.h"

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    _type = OperationType::None;
    _rect = nullptr;
}

void GraphicsView::setMapScene(QGraphicsScene *scene)
{
    auto s = (MapScene *) scene;
    connect (s, &MapScene::requestRepaint, this, [this]() {
        repaint();
    });
    QGraphicsView::setScene(scene);
}

void GraphicsView::zoomToFit()
{
    auto sc = (MapScene *) scene();
    auto rc = sc->contentBoundingBox();
    fitInView(rc, Qt::KeepAspectRatio);
    repaint();
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        _isPressed = true;
        _lastPoint = event->pos();
        _pressedScPoint = mapToScene(event->pos());
    } else {
        QGraphicsView::mousePressEvent(event);
    }

    auto sc = (MapScene *) scene();

    switch (_type) {
    case OperationType::Pan:
        setCursor(Qt::ClosedHandCursor);
        break;

    case OperationType::Zoom: {
        auto rc = sc->sceneRect();
        auto zoomWRatio = qreal(rc.width()) / sc->contentBoundingBox().width();
        auto zoomHRatio = qreal(rc.height()) / sc->contentBoundingBox().height();
        auto zoomRatio = min(zoomWRatio, zoomHRatio);

        Q_ASSERT(_rect == nullptr);
        _rect = sc->addRect(
                    QRectF(_pressedScPoint, QSizeF(0, 0)),
                    QPen(QColor(100, 100, 100), zoomRatio));
        _rect->setVisible(true);
        repaint();
        break;
    }

    default:
        break;
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    _isPressed = false;
    setCursor(Qt::ArrowCursor);
    auto sc = (MapScene *) scene();

    switch (_type) {
    case OperationType::Pan: {
        break;
    }

    case OperationType::Zoom:
        Q_ASSERT(_rect != nullptr);
        fitInView(_rect->rect(), Qt::KeepAspectRatio);
        sc->removeItem(_rect);
        repaint();
        _rect = nullptr;
        break;

    default:
        break;
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (!_isPressed) {
        return;
    }

    auto sc = (MapScene *) scene();

    switch (_type) {
    case OperationType::Pan: {
        static auto lastSceneRect = scene()->sceneRect();

        auto ps = mapToScene(_lastPoint);
        auto ts = mapToScene(event->pos());

        auto dx = ts.x() - ps.x();
        auto dy = ts.y() - ps.y();
        auto rc = lastSceneRect;

        rc.translate(-dx, -dy);
        lastSceneRect = rc;

        setSceneRect(rc);
        repaint();
        break;
    }

    case OperationType::Zoom: {
        auto ps = _pressedScPoint;
        auto ts = mapToScene(event->pos());

        auto dx = ts.x() - ps.x();
        auto dy = ts.y() - ps.y();

        Q_ASSERT(_rect != nullptr);
        _rect->setRect(QRectF(_pressedScPoint, QSizeF(dx, dy)));
        repaint();
        break;
    }

    default:
        break;
    }

    _lastPoint = event->pos();
}
