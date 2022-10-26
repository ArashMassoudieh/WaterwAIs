#ifndef MODELLAYER_H
#define MODELLAYER_H

#include "layer.h"
#include "object.h"

class ModelLayer: public Layer
{
public:
    ModelLayer();
    ModelLayer& operator=(const ModelLayer& other);
    virtual ~ModelLayer();
    ModelLayer(const ModelLayer& other);
    bool GetFromJsonDocument(const QJsonDocument &JsonDoc) override;
private:
    QMap<QString,Object> objects;

};

#endif // MODELLAYER_H
