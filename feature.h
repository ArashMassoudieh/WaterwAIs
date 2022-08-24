#ifndef FEATURE_H
#define FEATURE_H

#include <string>
#include "cpoint.h"
#include <QString>
enum class _FeatureType {MultiLineString, Unknown};

using namespace std;

class Feature
{
public:
    Feature();
    bool SetFeatureType(const string &FT);
    void SetFeatureType(_FeatureType FT);
    bool SetFeatureType(const QString &FT);
    _FeatureType GetFeatureType();
    Feature(const Feature&);
    Feature& operator = (const Feature &C);
    void AppendToGeometry(const CPoint &pt);
    static _FeatureType Feature_Type(const string &FT);
    vector<CPoint> GetGeometry();
private:
    _FeatureType FeatureType;
    vector<CPoint> geometry;
};

#endif // FEATURE_H
