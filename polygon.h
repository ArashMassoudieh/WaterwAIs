#ifndef POLYGON_H
#define POLYGON_H

#include "QGraphicsPolygonItem"

class Polygon : public QGraphicsPolygonItem
{
public:
    Polygon();
    Polygon(QPolygonF &plygon);
    Polygon(const Polygon &plygon);
    Polygon(Polygon *plygon);
    Polygon *operator=(const Polygon &plygon);

};

#endif // POLYGON_H
