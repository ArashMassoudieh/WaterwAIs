#ifndef DTNode_H
#define DTNode_H

#include <Circle.h>
#include <object.h>
#include <layer.h>

struct objectColor
{
    QColor color1, color2, defaultColor;
};

enum corners{ none, topleft, topright, bottomleft, bottomright };
enum edgesides{ noside, topside, leftside, bottomside, rightside };


class GraphicsView;


class DTNode:public Object, public Circle
{
public:
    DTNode();
    DTNode(GraphicsView *parent);
    DTNode(const Object &obj);
    DTNode(const QString &objecttype, const QJsonObject &jsonobject, GraphicsView *parent=nullptr);
    DTNode(const DTNode &);
    DTNode& operator=(const DTNode &);
    DTNode& operator=(const Object &);
    int type() const Q_DECL_OVERRIDE { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int Width() const {return  width;}
    int Height() const {return height;}
    corners corner(const int _x, const int _y);
    edgesides edge(const int x, const int y);
    void setWidth(const int& Width);
    void setHeight(const int& Height);
    double fontfactor();
    vector<double> bounds();
    QPixmap*GetIcon(const QString &type);


private:
    GraphicsView *parent = nullptr;
    int width = 200;
    int height = 200;
    bool bold = false;
    QPixmap *icon = nullptr;


};

#endif // DTNode_H
