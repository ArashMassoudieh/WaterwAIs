#include "object.h"

Object::Object():VariableList()
{

}

Object& Object::operator=(const Object& other)
{
    VariableList::operator=(other);
    SetObjectType(other.ObjectType());
    return *this;
}
Object::~Object()
{

}
Object::Object(const Object& other):VariableList(other)
{
    SetObjectType(other.ObjectType());
}
Object::Object(const QJsonObject& qjobject)
{

}
