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
    Object(const QString &ObjectType, const QJsonObject& qjobject);
    void SetName(const QString &_name) {name=_name;}
    QString Name() {return name;}
private:
    QString name;

};

#endif // OBJECT_H
