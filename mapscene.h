#ifndef MAPSCENE_H
#define MAPSCENE_H

#include "QGraphicsScene"
#include "layer.h"

class MapScene : public QGraphicsScene
{
public:
    MapScene();
    MapScene(QObject *qwidget);

    bool AppendLayer(Layer *layer);
    void addItem(QGraphicsItem *item);

    QRectF contentBoundingBox() const {
        return _rc;
    }

private:
    QRectF _rc;
    void updateBounding(const QRectF &rc);
};

#endif // MAPSCENE_H
