#ifndef MODELLAYER_H
#define MODELLAYER_H

#include "layer.h"
#include "node.h"
#include "metamodel.h"

class ModelLayer: public Layer
{
public:
    ModelLayer();
    ModelLayer& operator=(const ModelLayer& other);
    virtual ~ModelLayer();
    ModelLayer(const ModelLayer& other);
    bool GetFromJsonDocument(const QJsonDocument &JsonDoc) override;
    bool GetMetalModelFromJasonDocument(const QJsonDocument &JsonDoc);
    void SetMetaModel (const MetaModel &meta_model) {metamodel=meta_model;}
private:
    QMap<QString,Node> nodes;
    MetaModel metamodel;

};

#endif // MODELLAYER_H
