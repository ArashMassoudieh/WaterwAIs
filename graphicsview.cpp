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
    qDebug() << "=============== setMapScene";

    QGraphicsView::setScene(scene);

    Q_ASSERT(_rect == nullptr);
    _rect = scene->addRect(QRectF(0, 0, 0, 0), QPen(QColor(100, 100, 100), 1));
    _rect->setVisible(false);
}

void GraphicsView::zoomToFit()
{
    auto rc = scene()->sceneRect();
    fitInView(rc, Qt::KeepAspectRatio);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        _isPressed = true;
        _pressedPoint = event->pos();
        qDebug() << "- Pressed";
    }

    switch (_type) {
    case OperationType::Pan:
        setCursor(Qt::ClosedHandCursor);
        break;

    case OperationType::Zoom:
        _rect->setRect(QRectF(_pressedPoint, QSizeF(0, 0)));
        _rect->setVisible(true);
        break;

    default:
        break;
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    _isPressed = false;
    setCursor(Qt::ArrowCursor);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (!_isPressed) {
        return;
    }

    auto ps = mapToScene(_pressedPoint);
    auto ts = mapToScene(event->pos());

    auto dx = ts.x() - ps.x();
    auto dy = ts.y() - ps.y();
    auto sc = (MapScene *) scene();
    auto rc = sc->contentBoundingBox();

    switch (_type) {
    case OperationType::Pan: {
        rc.translate(-dx, -dy);
        setSceneRect(rc);
        repaint();
        break;
    }

    case OperationType::Zoom:
        _rect->setRect(QRectF(_pressedPoint, QSizeF(dx, dy)));
        break;

    default:
        break;
    }
}
