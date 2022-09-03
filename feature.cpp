#include "feature.h"
#include "segment.h"
#include "Circle.h"
#include "layer.h"
#include "polygon.h"

Feature::Feature(Layer *p)
{
    parent = p;
}

bool Feature::SetFeatureType(const string &FT)
{
    FeatureType = Feature_Type(FT);
    if (FeatureType==_FeatureType::Unknown)
        return false;
    else
        return true;
}

bool Feature::SetFeatureType(const QString &FT)
{
    FeatureType = Feature_Type(FT.toStdString());
    if (FeatureType==_FeatureType::Unknown)
        return false;
    else
        return true;
}

void Feature::SetFeatureType(_FeatureType FT)
{
    FeatureType = FT;
}

_FeatureType Feature::GetFeatureType()
{
    return FeatureType;
}


Feature::Feature(const Feature& C)
{
    geometry = C.geometry;
    FeatureType = C.FeatureType;
}
Feature& Feature::operator = (const Feature &C)
{
    geometry = C.geometry;
    FeatureType = C.FeatureType;
    return *this;
}

void Feature::AppendToGeometry(const CPoint &pt)
{
    geometry.push_back(pt);
}
vector<CPoint> Feature::GetGeometry()
{
    return geometry;
}

_FeatureType Feature::Feature_Type(const string &FT)
{
    if (FT=="MultiLineString")
    {
        return _FeatureType::MultiLineString;
    }

    return _FeatureType::Unknown;
}

bool Feature::GetGeometryFromJsonArray(const QJsonArray &array, _FeatureType FT)
{
    FeatureType = FT;
    if (FeatureType == _FeatureType::MultiLineString)
    {   for (int i=0; i<array.count(); i++)
        {
            QJsonArray level1 = array[i].toArray();
            for (int j=0; j<level1.size(); j++)
            {
                QJsonArray coords = level1[j].toArray();
                CPoint p;
                p.setx(coords[0].toDouble());
                p.sety(coords[1].toDouble());
                geometry.push_back(p);
            }
        }
    }
    else if (FeatureType == _FeatureType::Point)
    {
        QJsonArray coords = array;
        CPoint p;
        p.setx(coords[0].toDouble());
        p.sety(coords[1].toDouble());
        geometry.push_back(p);
    }
    else if (FeatureType == _FeatureType::MultiPolygon)
    {
        for (int i=0; i<array.count(); i++)
        {
            QJsonArray level1 = array[i].toArray();
            for (int j=0; j<level1.size(); j++)
            {
                QJsonArray level2 = level1[j].toArray();
                for (int k=0; k<level2.size(); k++)
                {
                    QJsonArray coords = level2[k].toArray();
                    CPoint p;
                    p.setx(coords[0].toDouble());
                    p.sety(coords[1].toDouble());
                    geometry.push_back(p);
                }
            }
        }
    }
    return true;
}


QVector<shared_ptr<QGraphicsItem>> Feature::toGraphicItems()
{
    QVector<shared_ptr<QGraphicsItem>> out;
    if (FeatureType==_FeatureType::MultiLineString)
    {   for (int i=0; i<geometry.size()-1; i++)
        {
            if (FeatureType == _FeatureType::MultiLineString)
            {   shared_ptr<Segment> seg( new Segment(geometry[i],geometry[i+1]));
                out.push_back(seg);
            }
        }
    }
    if (FeatureType == _FeatureType::Point)
    {   shared_ptr<Circle> circle( new Circle(geometry[0],50));
        out.push_back(circle);
    }
    if (FeatureType == _FeatureType::MultiPolygon)
    {   QPolygonF plygn;
        for (int i=0; i<geometry.size(); i++)
        {
            plygn.append(QPointF(geometry[i].x(),geometry[i].y()));
        }
        shared_ptr<Polygon> polygon( new Polygon(plygn));
        polygon->setPen(QPen(Qt::red));
        out.push_back(polygon);
    }
    return out;
}

double Feature::GetRange(range rng, dir dr)
{
    double extreme;
    if (!geometry.size())
        return 0;
    int range_i=0;
    if (rng==range::max)
        range_i=-1;
    else
        range_i = 1;
    extreme = range_i*1e12;
    for (int i=0; i<geometry.size(); i++)
    {
        if (dr==dir::x)
        {   if (range_i*geometry[i].x()<range_i*extreme)
                extreme = geometry[i].x();
        }
        else
        {
            if (range_i*geometry[i].y()<range_i*extreme)
                extreme = geometry[i].y();
        }
    }
    return extreme;
}

void Feature::ClearGraphicalObjects()
{
    for (int i=0; i<graphical_objects.size(); i++)
        if (graphical_objects[i]!=nullptr)
        delete(graphical_objects[i]);

    graphical_objects.clear();
}
