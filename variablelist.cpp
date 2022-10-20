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
        if (key=="type")
        {
            if(qjobject.value(key).toString() == "node")
                Object_Type = object_type::node;
            if(qjobject.value(key).toString() == "link")
                Object_Type = object_type::link;
        }
        else
        {   Variable var = Variable(qjobject.value(key).toObject());
            operator[](key) = var;
        }
    }
    Variable var;
    var.SetType(variable_type::string);
    operator[]("name") = var;
    if (ObjectType()==object_type::node)
    {
        Variable varxy;
        varxy.SetType(variable_type::value);
        operator[]("x") = varxy;
        operator[]("y") = varxy;
    }

}
