#include "node.h"
#include "graphicsview.h"


Node::Node()
{

}

Node::Node(GraphicsView *_parent):Object()
{

    parent = _parent;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
    setX(1000-width/2);
    setY(1000-height/2);
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

QRectF Node::boundingRect() const
{
    qreal adjust = 0;
    return QRectF( 0 - adjust, 0 - adjust, width + adjust, height + adjust);
}
QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal iconmargin = 0;
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.7);
    QColor Color1, Color2;
    painter->setBrush(Qt::white);
    QRadialGradient radialGrad(QPointF(width / 2, height / 2), min(width, height));
    radialGrad.setColorAt(0, QColor(Qt::lightGray).lighter(50));
    radialGrad.setColorAt(1, QColor(Qt::lightGray).lighter(-50));
    QPixmap pixmap;



    //if (IconFileName().contains("/"))
        pixmap = QPixmap(IconFileName());
    //else
        //pixmap = QPixmap(QString::fromStdString(RESOURCE_DIRECTORY+"/Icons/" + IconFileName()));
    QRectF rect = QRectF(boundingRect().left()*0 + iconmargin*boundingRect().width(), boundingRect().top()*0+iconmargin*boundingRect().width(), boundingRect().width()*(1-iconmargin), boundingRect().height()*(1-iconmargin));
    QRectF source(0, 0, pixmap.size().width(), pixmap.size().height());
    painter->drawPixmap(rect, pixmap, source);

    if (isSelected())
    {
        radialGrad.setColorAt(0, Qt::green);
        radialGrad.setColorAt(1, Qt::darkGreen);
    }

    painter->setPen(QPen(Qt::white, (bold) ? 2 : 0));
    painter->drawRoundRect(0, 0, width, height,10,10);
    painter->setPen(QPen(Qt::black, (bold) ? 2 : 0));
    qreal factor = parent->transform().scale(1, 1).mapRect(QRectF(0, 0, 1, 1)).width();
    int size = int(4 + 6 / factor)*fontfactor();
    QFont QF = painter->font(); QF.setPointSize(size);// QF.pointSize() + 2);
    QF.setBold(bold);
    painter->setFont(QF);

    //painter->drawText(10, height - 10, QString("%1: %2").arg(Object::T)).arg(QString::fromStdString(object()->GetName())));
    //qDebug() << "Node Paint Complete!";
}

void Node::setWidth(const int& _width)
{
    width = _width; update();
}
void Node::setHeight(const int& _height) {
    height = _height; update();
}

void Node::setX(const int& x)
{
    QGraphicsItem::setX(x);
}
void Node::setY(const int& y)
{
    QGraphicsItem::setY(y);
}

double Node::fontfactor(){
    if (parent)
        return parent->FontFactor();
    else
        return 1;
}


