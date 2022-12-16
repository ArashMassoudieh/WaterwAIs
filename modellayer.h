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
    void clickeme();
    QJsonDocument loadJson(const QString &fileName);
    QJsonDocument loadJson(QNetworkReply *fileName);
    QJsonDocument loadJson(QUrl fileName);
    bool prepareNodes(const QJsonDocument &JsonDoc);
    bool AddToScene(QGraphicsScene *scene);
    bool parsingMetaModelData(const QJsonDocument &JsonDoc);
    QMap<QString,QString> getSortedNodeData(){ return sortedNodeDataMap;};

private:
    QMap<QString,Node> nodes;
    QMap<QString,QString> modelDataMap;
    QMap<QString,QString> sortedNodeDataMap;
    MetaModel *metamodel = nullptr;

};

#endif // MODELLAYER_H
