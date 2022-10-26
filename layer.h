#ifndef LAYER_H
#define LAYER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImageReader>

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
    void SetColor(const QColor &c) {
        color = c;
        pen.setColor(c);
        emit colorChanged();
        emit penChanged();
    }
    QColor layerColor() const {
        return color;
    }

    void SetPen(const QPen &p) {pen = p;}
    QPen Pen() {return pen;}
    Feature *feature(size_t i);
    QString address;
    Downloader downloader;
    QJsonDocument JsonDoc;
    MapScene *Scene() {return scene;}
    void SetScene(MapScene *_scene) {scene = _scene;}

    QString layerName() const {
        return _name;
    }

    void setLayerName(const QString val) {
        _name = val;
    }

    QString layerIconUrl() const {
        return _iconUrl;
    }

    void setLayerIconUrl(const QString url) {
        _iconUrl = url;
        auto reply = nam.get(QNetworkRequest(url));

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            auto reader = new QImageReader(reply);
            _icon = QPixmap::fromImageReader(reader).scaled(QSize(24, 24));
            emit iconChanged();
            reply->deleteLater();
        });
    }

    QPixmap layerIcon() const {
        return _icon;
    }

    bool visible() const {
        return _visible;
    }

    void setVisible(bool val) {
        _visible = val;
        emit visibleChanged();
    }

    qreal layerOpacity() const {
        return _opacity;
    }

    void setOpacity(qreal val) {
        _opacity = val;
        emit opacityChanged();
    }

    void setLineType(Qt::PenStyle style) {
        pen.setStyle(style);
        emit penChanged();
    }

    void setLineWidth(int width) {
        pen.setWidth(width);
        emit penChanged();
    }

    int layerZ() const {
        return _z;
    }

    void setZ(int z) {
        _z = z;
        emit zChanged();
    }

private:
    QString _name;
    QString _iconUrl;
    QPixmap _icon;
    vector<Feature> features;
    _FeatureType FeatureType;
    QColor color;
    QPen pen;
    MapScene *scene=nullptr;
    QNetworkAccessManager nam;
    bool _visible = true;
    qreal _opacity = 1;
    int _z;

public slots:
    void OnDownloadFinished();

signals:
    void iconChanged();
    void visibleChanged();
    void penChanged();
    void colorChanged();
    void opacityChanged();
    void zChanged();
};

QJsonDocument loadJson(const QString &fileName);
QJsonDocument loadJson(QNetworkReply *fileName);
QJsonDocument loadJson(QUrl fileName);

#endif // LAYER_H
