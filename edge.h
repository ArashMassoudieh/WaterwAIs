#ifndef EDGE_H
#define EDGE_H

#include "object.h"
#include <QGraphicsItem>
#include "string"


class DTNode;
class GraphicsView;

enum class connected {to, from};

using namespace std;

class DTEdge : public Object, public QGraphicsLineItem
{
public:
    DTEdge();
    DTEdge(GraphicsView *parent);
    DTEdge(const Object &obj);
    DTEdge(const QString &objecttype, const QJsonObject &jsonobject, GraphicsView *parent=nullptr);
    DTEdge(const DTEdge &);
    DTEdge& operator=(const DTEdge &);
    DTEdge& operator=(const Object &);
    enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE { return Type; }
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void adjust();
    void SetConnectedNode(DTNode* node, connected source_dest);
    DTNode * ConnectedNode(connected source_dest);

private:
    GraphicsView *parent;
    DTNode *source;
    DTNode *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

public slots:

};


#endif // EDGE_H
