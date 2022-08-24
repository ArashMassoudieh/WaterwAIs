#include "layer.h"
#include "QJsonObject"
#include "QJsonArray"

Layer::Layer()
{

}

bool Layer::SetFeatureType(const string &FT)
{
    FeatureType = Feature::Feature_Type(FT);
    if (FeatureType==_FeatureType::Unknown)
        return false;
    else
        return true;
}
void Layer::SetFeatureType(_FeatureType FT)
{
    FeatureType = FT;
}
bool Layer::SetFeatureType(const QString &FT)
{
    FeatureType = Feature::Feature_Type(FT.toStdString());
    if (FeatureType==_FeatureType::Unknown)
        return false;
    else
        return true;
}
_FeatureType Layer::GetFeatureType()
{
    return FeatureType;
}
Layer::Layer(const Layer& L)
{
    features = L.features;
    FeatureType = L.FeatureType;
}
Layer& Layer::operator = (const Layer &L)
{
    features = L.features;
    FeatureType = L.FeatureType;
    return *this;
}
void Layer::AppendToFeatures(const Feature &feature)
{
    features.push_back(feature);
}

bool Layer::GetFromJsonDocument(const QJsonDocument &JsonDoc)
{
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);
        qDebug() << "Key = " << key << ", Value = " << value.toString();
    }
    QJsonArray features = JsonObject.value("features").toArray();
    for (int i=0; i<features.count(); i++) {
        QJsonObject value = features[i].toObject();
        QJsonObject geometry = value["geometry"].toObject();
        qDebug()<<"Geometry: " <<geometry;
        QJsonArray coordinates = geometry["coordinates"].toArray();
        QString type = geometry["type"].toString();
        qDebug() << "Key = " << i << ", Coordinates = " << coordinates << ", Type = " << type;
    }

    return true;
}
