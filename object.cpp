#include "object.h"
#include "QtCore/qjsonobject.h"

Object::Object():VariableList()
{

}

Object& Object::operator=(const Object& other)
{
    VariableList::operator=(other);
    SetObjectType(other.ObjectType());
    meta = other.meta;
    return *this;
}
Object::~Object()
{

}
Object::Object(const Object& other):VariableList(other)
{
    meta = other.meta;
    SetObjectType(other.ObjectType());
}
Object::Object(const QString &objectType, const QJsonObject& qjobject):VariableList(objectType, qjobject)
{

}

Object::Object(const QString &Name, const QString &ComponentType, const VariableList& variables):VariableList(variables)
{
    SetComponentType(ComponentType);
    name = Name;
}

void Object::SetMetaModel(MetaModel *_meta)
{
    meta = _meta;
}

