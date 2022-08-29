#ifndef LAYER_H
#define LAYER_H

#include "feature.h"
#include "QJsonDocument"
#include "QRectF"
#include "QColor"
#include "QPen"

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
    void SetColor(const QColor &c) {color = c; pen.setColor(c);}
    void SetPen(const QPen &p) {pen = p;}
    QPen Pen() {return pen;}
    Feature *feature(int i);

private:
    vector<Feature> features;
    _FeatureType FeatureType;
    QColor color;
    QPen pen;

};

#endif // LAYER_H
