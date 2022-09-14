#include <QDebug>
#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
}

void GraphicsView::zoomToFit()
{
    double c = 1000;
    auto rc = scene()->sceneRect();
    rc.setLeft(rc.left() / c);
    rc.setTop(rc.top() / c);
    rc.setRight(rc.right() / c);
    rc.setBottom(rc.bottom() / c);

    fitInView(rc, Qt::KeepAspectRatio);
}
