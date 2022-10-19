#ifndef OBJECT_H
#define OBJECT_H

#include "variablelist.h"

enum class object_type {block, link, entity};

class Object:public VariableList
{
public:
    Object();
    Object& operator=(const Object& other);
    virtual ~Object();
    Object(const Object& other);
    Object(QJsonDocument& qjobject);
private:
    object_type ObjectType;
};

#endif // OBJECT_H
