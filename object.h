#ifndef OBJECT_H
#define OBJECT_H

#include "variablelist.h"
#include <QJsonObject>

class Object:public VariableList
{
public:
    Object();
    Object& operator=(const Object& other);
    virtual ~Object();
    Object(const Object& other);
    Object(const QJsonObject& qjobject);
private:

};

#endif // OBJECT_H
