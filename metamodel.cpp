#include "metamodel.h"
#include <QJsonObject>
MetaModel::MetaModel():QMap<QString,VariableList>()
{

}

MetaModel& MetaModel::operator=(const MetaModel& other)
{
    QMap<QString,VariableList>::operator=(other);
    return *this;
}

MetaModel::~MetaModel()
{

}
MetaModel::MetaModel(const MetaModel& other):QMap<QString,VariableList>(other)
{

}
MetaModel::MetaModel(QJsonDocument& qjdoc):QMap<QString,VariableList>()
{
    QJsonObject qjobject = qjdoc.object();
    foreach(const QString& key, qjobject.keys()) {
        VariableList varlist = VariableList(qjobject.value(key).toObject());
        operator[](key) = varlist;
    }
}

bool MetaModel::getloadIcon(const QJsonDocument &JsonDoc){
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);
        qDebug() << "Key = " << key << ", Value = " << value.toString();
    }

    if (JsonObject.contains("name")) {
        auto name = JsonObject.value("name").toString();
       this->setLayerName(name);
    }

    if (JsonObject.contains("icon")) {
        auto iconUrl = JsonObject.value("icon").toString();
        this->downloadIcon(iconUrl);
    }

    return true;
}
