#ifndef OBJECT_H
#define OBJECT_H

#include "variablelist.h"


class Object:public VariableList
{
public:
    Object();
    Object& operator=(const Object& other);
    virtual ~Object();
    Object(const Object& other);
    Object(QJsonObject& qjobject);
private:

};

#endif // OBJECT_H
