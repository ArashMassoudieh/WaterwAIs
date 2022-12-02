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

bool MetaModel::getloadIcon(const QString &fileName){
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    QJsonDocument JsonDoc = QJsonDocument().fromJson(jsonFile.readAll());
    qDebug()<<"ModelJsonDoc2000 '"<<JsonDoc << "' 00000000";
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);
        qDebug() << "Key = " << key << ", Value = " << value.toString();
        if(key == "sub-catchment"){
            auto iconUrl =  value.toObject().value("icon").toString();
            auto name =  value.toObject().value("name").toString();
             this->downloadIcon(iconUrl);
        }
    }

    return true;
}
