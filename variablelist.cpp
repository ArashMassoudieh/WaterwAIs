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

bool VariableList::SetValue(const QString &VariableName, const QString &Value)
{
    if (count(VariableName)!=0)
    {
        operator[](VariableName).SetValue(Value);
        return true;
    }
    else
        return false;
}


Variable& VariableList::operator[](const QString name)
{
    return QMap<QString, Variable>::operator[](name);
}

NameValuePair VariableList::operator[](int i)
{
    if (i>count()-1) return NameValuePair();
    QMap<QString, Variable>::iterator it = begin()+i;
    NameValuePair out;
    out.Name = it.key();
    out.Var = &it.value();
    return out;
}

//VariableList::VariableList(const QJsonObject& qjobject):QMap<QString,Variable>() //for instances
//{


//    foreach(const QString& key, qjobject.keys()) {
//        if (key=="icon")
//            iconfilename = qjobject.value(key).toString();
//        if (key=="type")
//        {
//            component_type = qjobject.value(key).toString();
//        }
//        else
//        {   Variable var = Variable(qjobject.value(key).toObject());
//            operator[](key) = var;
//        }
//    }
//    Variable var;
//    var.SetType(variable_type::string);
//    operator[]("name") = var;
//    if (ObjectType()==object_type::node)
//    {
//        Variable varxy;
//        varxy.SetType(variable_type::value);
//        operator[]("x") = varxy;
//        operator[]("y") = varxy;
//    }

//}

//This function for model layer json data types
VariableList::VariableList(const QJsonObject& qjobject):QMap<QString,Variable>() //for modellayer data instances
{
    foreach(const QString& key, qjobject.keys()) {
        if (key=="x")
        {
            Variable varx;
            varx.SetType(variable_type::value);
            operator[]("x") = varx;
        }
        else if (key=="y")
        {
            Variable vary;
            vary.SetType(variable_type::value);
            operator[]("y") = vary;
        }
        else
        {   //Variable var = Variable(key, qjobject.value(key).toObject());
            Variable var;
            var.SetType(variable_type::string);
            operator[](key) = var;
        }
    }
}

bool VariableList::AddXYNameVariables()
{
    if (count("name")==0)
    {   Variable var;
        var.SetType(variable_type::string);
        operator[]("name") = var;
    }
    if (ObjectType()==object_type::node && count("x")==0)
    {
        Variable varxy;
        varxy.SetType(variable_type::value);
        operator[]("x") = varxy;
        operator[]("y") = varxy;
    }
    return true;
}
bool VariableList::AddNameVariable()
{
    if (count("name")==0)
    {   Variable var;
        var.SetType(variable_type::string);
        operator[]("name") = var;
    }
    return true;
}
