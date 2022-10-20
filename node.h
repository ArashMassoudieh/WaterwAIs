#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <object.h>

struct objectColor
{
    QColor color1, color2, defaultColor;
};

enum corners{ none, topleft, topright, bottomleft, bottomright };
enum edgesides{ noside, topside, leftside, bottomside, rightside };


class GraphicsView;

class Node:public QGraphicsItem, Object
{
public:
    Node();
    Node(GraphicsView *parent);
    Node(const Node &);
    objectColor color;
    Node operator=(const Node &);
    int type() const Q_DECL_OVERRIDE { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    Object *object();
    int Width() const {return  width;}
    int Height() const {return height;}
    corners corner(const int _x, const int _y);
    edgesides edge(const int x, const int y);
    void setWidth(const int& Width);
    void setHeight(const int& Height);
    void setX(const int& x);
    void setY(const int& y);
    double fontfactor();
private:
    GraphicsView *parent;
    int width = 200;
    int height = 200;
    bool bold = false;
};

#endif // NODE_H
