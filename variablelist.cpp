#include "variablelist.h"
#include <QJsonObject>

VariableList::VariableList():QMap<QString,Variable>()
{

}


VariableList& VariableList::operator=(const VariableList& other)
{
    QMap<QString,Variable>::operator=(other);
    iconfilename = other.iconfilename;
    return *this;
}

VariableList::~VariableList()
{

}
VariableList::VariableList(const VariableList& other):QMap<QString,Variable>(other)
{
    iconfilename = other.iconfilename;
}
VariableList::VariableList(const QJsonObject& qjobject):QMap<QString,Variable>()
{

    foreach(const QString& key, qjobject.keys()) {
        if (key=="icon")
            iconfilename = qjobject.value(key).toString();
        else
        {   Variable var = Variable(qjobject.value(key).toObject());
            operator[](key) = var;
        }
    }

}
