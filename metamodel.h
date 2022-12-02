#ifndef METAMODEL_H
#define METAMODEL_H


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <variablelist.h>
#include "feature.h"
#include "QJsonDocument"
#include "QRectF"
#include "QColor"
#include "QPen"
#include "filedownloader.h"
#include "object.h"
#include "mainwindow.h"

//This class contains the information about all types of nodes and links that can be used in the model

class MapScene;
class MetaModel: public QObject ,public QMap<QString,VariableList>
{
Q_OBJECT

public:
    MetaModel();
    MetaModel& operator=(const MetaModel& other);
    virtual ~MetaModel();
    MetaModel(const MetaModel& other);
    MetaModel(QJsonDocument& qjobject);
    virtual bool getloadIcon(const QString &fileName);

    QString layerName() const {
        return _name;
    }

    void setLayerName(const QString val) {
        _name = val;
    }

    QString layerIconUrl() const {
        return _iconUrl;
    }
    void downloadIcon(const QString url) {
        _iconUrl = url;
        auto reply = nam.get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            auto reader = new QImageReader(reply);
            _icon = QPixmap::fromImageReader(reader).scaled(QSize(24, 24));
            emit iconChanged();
            reply->deleteLater();
        });
    }

private:
    QString _name;
    QPixmap _icon;
    QNetworkAccessManager nam;
    QString _iconUrl;

signals:
    void iconChanged();
    void visibleChanged();
    void penChanged();
    void colorChanged();
    void opacityChanged();
    void zChanged();
};

#endif // METAMODEL_H
