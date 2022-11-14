#include "node.h"
#include "graphicsview.h"
#include <QStyleOptionGraphicsItem>


Node::Node():Circle()
{

}

Node::Node(GraphicsView *_parent):Object()
{

    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(this->zValue());
    parent->scene()->addItem(this);
}

Node::Node(const QJsonObject &jsonobject, GraphicsView *_parent):Object(jsonobject)
{
    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(this->zValue());
    parent->scene()->addItem(this);


}

Node::Node(const Node &E):Object(E)
{
    setFlags(E.flags());
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(E.zValue());
    setPos(E.pos());
    setFlag(ItemSendsGeometryChanges);
    width = E.Width();
    height = E.Height();
    parent = E.parent;

}


Node Node::operator=(const Node &E)
{
    Object::operator=(E);
    setFlags(E.flags());
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(E.zValue());
    setPos(E.pos());
    setFlag(ItemSendsGeometryChanges);
    width = E.Width();
    height = E.Height();
    parent = E.parent;
    return *this;
}

Node Node::operator=(const Object &E)
{
    Object::operator=(E);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setFlag(ItemSendsGeometryChanges);
    return *this;
}

QRectF Node::boundingRect() const
{
    return QRectF(x()-width/2, y()-height/2, width, height);

}
QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? Color().darker(150) : Color();
    if (option->state & QStyle::State_MouseOver) {
        fillColor = fillColor.lighter(125);
    }

    SetColor(Qt::black);
    painter->setPen(Pen());

    painter->setBrush(Qt::black);
    qDebug() << x() << "," << y();
    painter->drawEllipse(x()-width/2,y()-height/2,width, height);
}

void Node::setWidth(const int& _width)
{
    width = _width; update();
}
void Node::setHeight(const int& _height) {
    height = _height; update();
}

double Node::fontfactor(){
    if (parent)
        return parent->FontFactor();
    else
        return 1;
}

vector<double> Node::bounds()
{
    vector<double> out;
    out.push_back(x()-width/2 );
    out.push_back(y()-height/2 );
    out.push_back(x()+width/2);
    out.push_back(y()+height/2);

    return out;
}

