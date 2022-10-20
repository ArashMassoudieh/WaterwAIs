#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <object.h>

class GraphicsView;

class Node:public QGraphicsItem, Object
{
public:
    Node();
    Node(GraphicsView *parent);
};

#endif // NODE_H
