#include "node.h"
#include "graphicsview.h"
#include <QStyleOptionGraphicsItem>
#include "metamodel.h"
#include "Common.h"
#include <QDialog>
#include "about.h"


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

Node::Node(const QString &objectType, const QJsonObject &jsonobject, GraphicsView *_parent):Object(objectType, jsonobject)
{
    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(this->zValue());
    if (parent)
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
    meta = E.meta;
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
    meta = E.meta;
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
         about *myModel = new about();
         myModel->setWindowTitle("Node");
            myModel->show();
    }

    SetColor(Qt::black);
    painter->setPen(Pen());


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

void Node::SetMetaModel(MetaModel *_meta)
{
    meta = _meta;
}

QPixmap* Node::GetIcon(const QString &type)
{
    if (icon!=nullptr) return icon;
    qDebug() << type << ",";
    QString iconurl = HOST_PATH + meta->layerIconUrl();
    QString Iconfilename = HOST_PATH + meta->operator[](type).IconFileName();
    QString ObjectType = type;
    icon = new QPixmap(Iconfilename);
    return icon;
}
