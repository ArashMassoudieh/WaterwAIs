#include "variablelist.h"
#include <QJsonObject>

VariableList::VariableList():QMap<QString,Variable>()
{

}


VariableList& VariableList::operator=(const VariableList& other)
{
    QMap<QString,Variable>::operator=(other);
    iconfilename = other.iconfilename;
    component_type = other.component_type;
    Object_Type = other.Object_Type;
    return *this;
}

VariableList::~VariableList()
{

}
VariableList::VariableList(const VariableList& other):QMap<QString,Variable>(other)
{
    component_type = other.component_type;
    Object_Type = other.Object_Type;
    iconfilename = other.iconfilename;
}
VariableList::VariableList(const QString& objectType, const QJsonObject& qjobject):QMap<QString,Variable>() //for meta model
{

    component_type = objectType;
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

VariableList::VariableList(const QJsonObject& qjobject):QMap<QString,Variable>() //for instances
{


    foreach(const QString& key, qjobject.keys()) {
        if (key=="icon")
            iconfilename = qjobject.value(key).toString();
        if (key=="type")
        {
            component_type = qjobject.value(key).toString();
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
