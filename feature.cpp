#include "feature.h"

Feature::Feature()
{

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

bool Feature::GetGeometryFromJsonArray(const QJsonArray &array)
{
    for (int i=0; i<array.count(); i++)
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
    return true;
}
