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
