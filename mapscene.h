#ifndef MAPSCENE_H
#define MAPSCENE_H

#include "QGraphicsScene"
#include "layer.h"

class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene();
    MapScene(QObject *qwidget);

    bool AppendLayer(Layer *layer);
    void addItem(QGraphicsItem *item);

    QRectF contentBoundingBox() const {
        return _rc;
    }

signals:
    void requestRepaint();

private:
    QRectF _rc;
    void updateBounding(const QRectF &rc);
};

#endif // MAPSCENE_H
