#ifndef MODELLAYER_H
#define MODELLAYER_H

#include "layer.h"
#include "node.h"
#include "metamodel.h"

class QGraphicsScene;

class ModelLayer: public Layer
{
public:
    ModelLayer();
    ModelLayer& operator=(const ModelLayer& other);
    virtual ~ModelLayer();
    ModelLayer(const ModelLayer& other);
    bool GetFromJsonDocument(const QJsonDocument &JsonDoc) override;
    bool GetMetalModelFromJsonDocument(const QJsonDocument &JsonDoc);
    void SetMetaModel (MetaModel *meta_model) {metamodel=meta_model;}
    QJsonDocument loadJson(const QString &fileName);
    QJsonDocument loadJson(QNetworkReply *fileName);
    QJsonDocument loadJson(QUrl fileName);
    bool prepareNodes(const QString &fileName);
    bool AddToScene(QGraphicsScene *scene);
private:
    QMap<QString,Node> nodes;
    MetaModel *metamodel = nullptr;

};

#endif // MODELLAYER_H
