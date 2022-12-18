#ifndef EDGE_H
#define EDGE_H

#include "object.h"
#include <QGraphicsItem>
#include "string"


class Node;
class GraphicsView;


using namespace std;

class Edge : public QGraphicsItem
{
public:
    Edge(GraphicsView *parent);
    Edge(Node *sourceNode, Node *destNode, const QString &edgeType, GraphicsView *_parent = nullptr);
    Edge(Node *sourceNode, Node *destNode, GraphicsView *_parent=nullptr);
    Edge(Edge &E);
    void adjust();
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
    Object_Types itemType = Object_Types::Connector;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    bool bold = false;
    void setBold(const bool _Bold = true);
    objectColor color;
    bool avoidCrossObjects = true;
    Object *object();
    Node* sourceNode() {return source;}
    Node* destNode() {return dest;}
    int dist(const QPointF point);
    enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE{ return Type; }

private:
    GraphicsView *parent;
    Node *source;
    Node *dest;
    QColor GetColor(const string &clrstring);
public slots:
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};


#endif // EDGE_H
