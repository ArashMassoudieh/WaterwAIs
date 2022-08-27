#ifndef LAYER_H
#define LAYER_H

#include "feature.h"
#include "QJsonDocument"
#include "QRectF"

class Layer
{
public:
    Layer();
    bool SetFeatureType(const string &FT);
    void SetFeatureType(_FeatureType FT);
    bool SetFeatureType(const QString &FT);
    bool GetFromJsonDocument(const QJsonDocument &JsonDoc);
    _FeatureType GetFeatureType();
    Layer(const Layer&);
    Layer& operator = (const Layer &C);
    void AppendToFeatures(const Feature &feature);
    QVector<QVector<shared_ptr<QGraphicsItem>>> toGraphicItems();
    double GetRange(range rng, dir dr);
    QRectF GetBoundingRect();

private:
    vector<Feature> features;
    _FeatureType FeatureType;

};

#endif // LAYER_H
