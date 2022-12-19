#ifndef MODELLAYER_H
#define MODELLAYER_H

#include "layer.h"
#include "node.h"
#include "edge.h"
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


private:
    QMap<QString,DTNode> nodes;
    QMap<QString,DTEdge> edges;
    MetaModel *metamodel = nullptr;

};

#endif // MODELLAYER_H
