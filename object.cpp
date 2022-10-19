#include "object.h"

Object::Object():VariableList()
{

}

Object& Object::operator=(const Object& other)
{
    VariableList::operator=(other);
    ObjectType = other.ObjectType;
    return *this;
}
Object::~Object()
{

}
Object::Object(const Object& other):VariableList(other)
{
    ObjectType = other.ObjectType;
}
Object::Object(QJsonDocument& qjobject)
{

}
