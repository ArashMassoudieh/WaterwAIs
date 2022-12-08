#ifndef NODE_H
#define NODE_H

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
class MetaModel;

class Node:public Object, public Circle
{
public:
    Node();
    Node(GraphicsView *parent); // needs to be implemented
    Node(const Object &obj);
    Node(const QString &objecttype, const QJsonObject &jsonobject, GraphicsView *parent=nullptr);
    Node(const Node &);
    Node operator=(const Node &);
    Node operator=(const Object &); //needs to be implemented
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
    void SetMetaModel(MetaModel*);
    QPixmap*GetIcon(const QString &type);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

//    QString GetIcon(const QString &type);

private:
    GraphicsView *parent = nullptr;
    int width = 200;
    int height = 200;
    bool bold = false;
    MetaModel *meta;
    QPixmap *icon = nullptr;


};

#endif // NODE_H
