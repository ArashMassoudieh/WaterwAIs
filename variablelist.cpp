#include "variablelist.h"
#include <QJsonObject>

VariableList::VariableList():QMap<QString,Variable>()
{

}


VariableList& VariableList::operator=(const VariableList& other)
{
    QMap<QString,Variable>::operator=(other);
}

VariableList::~VariableList()
{

}
VariableList::VariableList(const VariableList& other):QMap<QString,Variable>(other)
{

}
VariableList::VariableList(const QJsonObject& qjobject):QMap<QString,Variable>()
{
    foreach(const QString& key, qjobject.keys()) {
        Variable var = Variable(qjobject.value(key).toObject());
        operator[](key) = var;
    }

}
