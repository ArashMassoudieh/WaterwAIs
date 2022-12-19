#include "node.h"
#include "graphicsview.h"
#include <QStyleOptionGraphicsItem>
#include "metamodel.h"
#include "Common.h"
#include <QDialog>
#include "about.h"


DTNode::DTNode()
{
    setData(1000,"DTNode");
    AddXYNameVariables();
}

DTNode::DTNode(GraphicsView *_parent):Object()
{

    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(this->zValue());
    parent->scene()->addItem(this);
    setData(1000,"DTNode");
    AddXYNameVariables();
}

DTNode::DTNode(const QString &objectType, const QJsonObject &jsonobject, GraphicsView *_parent):Object(objectType, jsonobject)
{
    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(this->zValue());
    if (parent)
        parent->scene()->addItem(this);

    setData(1000,"DTNode");
    AddXYNameVariables();
}

DTNode::DTNode(const DTNode &E):Object(E)
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
    AddXYNameVariables();
    setData(1000,"DTNode");

}


DTNode& DTNode::operator=(const DTNode &E)
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
    AddXYNameVariables();
    return *this;
}

DTNode& DTNode::operator=(const Object &E)
{
    Object::operator=(E);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setFlag(ItemSendsGeometryChanges);
    AddXYNameVariables();
    return *this;
}

QRectF DTNode::boundingRect() const
{
    return QRectF(x()-width/2, y()-height/2, width, height);

}
QPainterPath DTNode::shape() const
{
    QPainterPath path;
    path.addRect(14, 14, 82, 42);
    return path;
}

void DTNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPixmap *pixmap = GetIcon(ComponentType());
    double iconmargin = 0;
    QRectF rect = QRectF(boundingRect().left()*0 + iconmargin*boundingRect().width(),
                         boundingRect().top()*0+iconmargin*boundingRect().width(),
                         boundingRect().width()*(1-iconmargin)-100,
                         boundingRect().height()*(1-iconmargin)-100);
    QRectF source(0, 0, pixmap->size().width()+100, pixmap->size().height());



    painter->drawPixmap(rect, *pixmap, source);

    painter->setBrush(Qt::black);
    qDebug() << x() << "," << y();
    //painter->drawEllipse(x()-width/2,y()-height/2,width, height);
}

void DTNode::setWidth(const int& _width)
{
    width = _width; update();
}
void DTNode::setHeight(const int& _height) {
    height = _height; update();
}

double DTNode::fontfactor(){
    if (parent)
        return parent->FontFactor();
    else
        return 1;
}

vector<double> DTNode::bounds()
{
    vector<double> out;
    out.push_back(x()-width/2 );
    out.push_back(y()-height/2 );
    out.push_back(x()+width/2);
    out.push_back(y()+height/2);

    return out;
}


QPixmap* DTNode::GetIcon(const QString &type)
{
    if (icon!=nullptr) return icon;
    qDebug() << type << ",";
    QString iconurl = HOST_PATH + GetMetaModel()->layerIconUrl();
    QString Iconfilename = HOST_PATH + GetMetaModel()->operator[](type).IconFileName();
    QString ObjectType = type;
    icon = new QPixmap(Iconfilename);
    return icon;
}
