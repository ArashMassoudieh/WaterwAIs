#ifndef NODE_H
#define NODE_H

#include <Circle.h>
#include <object.h>

struct objectColor
{
    QColor color1, color2, defaultColor;
};

enum corners{ none, topleft, topright, bottomleft, bottomright };
enum edgesides{ noside, topside, leftside, bottomside, rightside };


class GraphicsView;

class Node:public Circle, Object
{
public:
    Node();
    Node(GraphicsView *parent);
    Node(const QJsonObject &jsonobject, GraphicsView *parent);
    Node(const Node &);
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
    double fontfactor();
    vector<double> bounds();

private:
    GraphicsView *parent;
    int width = 200;
    int height = 200;
    bool bold = false;

};

#endif // NODE_H
