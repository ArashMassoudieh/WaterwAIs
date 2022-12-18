#ifndef OBJECT_H
#define OBJECT_H

#include "variablelist.h"
#include <QJsonObject>

class MetaModel;

class Object:public VariableList
{
public:
    Object();
    Object& operator=(const Object& other);
    virtual ~Object();
    Object(const Object& other);
    Object(const QString &ObjectType, const QJsonObject& qjobject);
    Object(const QString &Name, const QString &Component_Type, const VariableList& variables);
    void SetName(const QString &_name) {name=_name;}
    QString Name() {return name;}
    void SetMetaModel(MetaModel*);
    MetaModel *GetMetaModel() {return meta;}
private:
    QString name;
    MetaModel *meta;

};

#endif // OBJECT_H
