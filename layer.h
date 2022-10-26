#ifndef LAYER_H
#define LAYER_H

#include "feature.h"
#include "QJsonDocument"
#include "QRectF"
#include "QColor"
#include "QPen"
#include "filedownloader.h"

class MapScene;

class Layer : public QObject
{
Q_OBJECT

public:
    explicit Layer(QObject *parent = 0);
    bool SetFeatureType(const string &FT);
    void SetFeatureType(_FeatureType FT);
    bool SetFeatureType(const QString &FT);
    virtual bool GetFromJsonDocument(const QJsonDocument &JsonDoc);
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
    QString address;
    Downloader downloader;
    QJsonDocument JsonDoc;
    MapScene *Scene() {return scene;}
    void SetScene(MapScene *_scene) {scene = _scene;}

private:
    vector<Feature> features;
    _FeatureType FeatureType;
    QColor color;
    QPen pen;
    MapScene *scene=nullptr;

public slots:
    void OnDownloadFinished();
};

QJsonDocument loadJson(const QString &fileName);
QJsonDocument loadJson(QNetworkReply *fileName);
QJsonDocument loadJson(QUrl fileName);

#endif // LAYER_H
