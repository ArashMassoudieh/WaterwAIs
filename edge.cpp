#include "edge.h"
#include "node.h"
#include "qpainter.h"
#include "graphicsview.h"
#include "mainwindow.h"
#include "QGraphicsSceneContextMenuEvent"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


DTEdge::DTEdge():Object()
{
    setData(1000,"DTEdge");
    SetObjectType(object_type::link);
    AddNameVariable();

}


DTEdge::DTEdge(GraphicsView *_parent):Object()
{
    parent = _parent;
    setData(1000,"DTEdge");
    SetObjectType(object_type::link);
    AddNameVariable();

}

DTEdge::DTEdge(const Object &obj):Object(obj)
{
    setData(1000,"DTEdge");
    SetObjectType(object_type::link);
    AddNameVariable();
}
DTEdge::DTEdge(const QString &objecttype, const QJsonObject &jsonobject, GraphicsView *_parent):Object(objecttype, jsonobject)
{
    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(this->zValue());
    if (parent)
        parent->scene()->addItem(this);

    setData(1000,"DTEdge");
    AddNameVariable();
}
DTEdge::DTEdge(const DTEdge &E):Object(E)
{
    setFlags(E.flags());
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(E.zValue());
    setPos(E.pos());
    setFlag(ItemSendsGeometryChanges);
    parent = E.parent;
    AddNameVariable();
    setData(1000,"DTEdge");
}
DTEdge& DTEdge::operator=(const DTEdge &E)
{
    Object::operator=(E);
    setFlags(E.flags());
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(E.zValue());
    setPos(E.pos());
    setFlag(ItemSendsGeometryChanges);
    parent = E.parent;
    AddNameVariable();
    setData(1000,"DTEdge");
    return *this;
}
DTEdge& DTEdge::operator=(const Object &E)
{
    Object::operator=(E);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setFlag(ItemSendsGeometryChanges);
    AddNameVariable();
    setData(1000,"DTEdge");
    return *this;
}

QRectF DTEdge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 8.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


void DTEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor objectcolor;
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;


    // Draw the line itself
    if (isSelected())
        painter->setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else
        painter->setPen(QPen(objectcolor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter->drawLine(line);

    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
        cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
        cos(angle - Pi + Pi / 3) * arrowSize);
    if (isSelected())
        painter->setBrush(Qt::green);
    else
        painter->setBrush(objectcolor);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);


}

void DTEdge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, source->Width() / 2, source->Height() / 2), mapFromItem(dest, dest->Width() / 2, dest->Height() / 2));

    prepareGeometryChange();

    qreal Ox, Oy, Dx, Dy;

    if (abs(line.dx()) < 1)
    {
        Ox = 0;
        Dx = 0;
    }
    else
    {
        Ox = line.dx() / abs(line.dx())*min(int(source->Width() / 2), int(fabs(source->Height() / 2.0 * line.dx() / (line.dy()+0.5))));
        Dx = -line.dx() / abs(line.dx())*min(int(dest->Width() / 2), int(fabs(dest->Height() / 2.0 * line.dx() / (line.dy()+0.5))));
    }
    if (abs(line.dy()) < 1)
    {
        Oy = 0;
        Dy = 0;
    }
    else
    {
        Oy = line.dy() / abs(line.dy())*min(int(source->Height() / 2), int(fabs(source->Width()/ 2.0 * line.dy() / (line.dx()+0.5))));
        Dy = -line.dy() / abs(line.dy())*min(int(dest->Height() / 2), int(fabs(dest->Width() / 2.0 * line.dy() / (line.dx()+0.5))));
    }
        QPointF edgeOffsetSource(Ox, Oy);
        QPointF edgeOffsetDest(Dx, Dy);
        sourcePoint = line.p1() + edgeOffsetSource;
        destPoint = line.p2()  + edgeOffsetDest;
}

void DTEdge::SetConnectedNode(DTNode* node, connected source_dest)
{
    if (source_dest == connected::from)
    {
        source = node;
    }
    else
    {
        dest = node;
    }

}

DTNode *DTEdge::ConnectedNode(connected source_dest)
{
    if (source_dest == connected::from)
    {
        return source;
    }
    else
    {
        return dest;
    }
}
