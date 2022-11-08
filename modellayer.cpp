#include "modellayer.h"
#include <QJsonObject>


ModelLayer::ModelLayer():Layer()
{

}

ModelLayer& ModelLayer::operator=(const ModelLayer& other)
{
    Layer::operator=(other);
    nodes = other.nodes;
    return *this;
}
ModelLayer::~ModelLayer()
{
    nodes.clear();

}
ModelLayer::ModelLayer(const ModelLayer& other):Layer(other)
{
    nodes = other.nodes;
}
bool ModelLayer::GetFromJsonDocument(const QJsonDocument &JsonDoc)
{
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);
        Object obj(value.toObject());
        nodes[key] = obj;
    }
    return true;
}



