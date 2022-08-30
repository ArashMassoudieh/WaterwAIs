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
};

#endif // MAPSCENE_H
