#include "modellayer.h"
#include <QJsonObject>


ModelLayer::ModelLayer():Layer()
{

}

ModelLayer& ModelLayer::operator=(const ModelLayer& other)
{
    Layer::operator=(other);
    objects = other.objects;
    return *this;
}
ModelLayer::~ModelLayer()
{
    objects.clear();

}
ModelLayer::ModelLayer(const ModelLayer& other):Layer(other)
{
    objects = other.objects;
}
bool ModelLayer::GetFromJsonDocument(const QJsonDocument &JsonDoc)
{
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);
        Object obj(value.toObject());
        objects[key] = obj;
    }
    return true;
}



