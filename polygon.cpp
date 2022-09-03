#include "polygon.h"
#include "QBrush"

Polygon::Polygon()
{

}

Polygon::Polygon(QPolygonF &plygon):QGraphicsPolygonItem(plygon)
{

}

Polygon::Polygon(const Polygon &plygon)
{
    setPolygon(plygon.polygon());
    setBrush(plygon.brush());
}

Polygon::Polygon(Polygon *plygon)
{
    setPolygon(plygon->polygon());
    setBrush(plygon->brush());
}

Polygon *Polygon::operator=(const Polygon &plygon)
{
    setPolygon(plygon.polygon());
    setBrush(plygon.brush());
    return this;
}

