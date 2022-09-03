#ifndef FEATURE_H
#define FEATURE_H

#include <string>
#include "cpoint.h"
#include <QString>
#include "QJsonArray"
#include "QGraphicsItem"
#include "QVector"

class Layer;

enum class _FeatureType {MultiLineString, Point, MultiPolygon, Unknown};

using namespace std;

class Feature
{
public:
    Feature(Layer *parent=nullptr);
    bool SetFeatureType(const string &FT);
    void SetFeatureType(_FeatureType FT);
    bool SetFeatureType(const QString &FT);
    _FeatureType GetFeatureType();
    Feature(const Feature&);
    Feature& operator = (const Feature &C);
    void AppendToGeometry(const CPoint &pt);
    static _FeatureType Feature_Type(const string &FT);
    vector<CPoint> GetGeometry();
    bool GetGeometryFromJsonArray(const QJsonArray &array, _FeatureType FT=_FeatureType::Unknown);
    QVector<shared_ptr<QGraphicsItem>> toGraphicItems();
    double GetRange(range rng, dir dr);
    vector<QGraphicsItem*> &GetGraphicalObjects() {return graphical_objects;}
    void ClearGraphicalObjects();
    Layer *Parent() {return parent;}
    void SetParent(Layer *p) {parent = p;}
private:
    _FeatureType FeatureType;
    vector<CPoint> geometry;
    Layer *parent;
    vector<QGraphicsItem*> graphical_objects;

};

#endif // FEATURE_H
