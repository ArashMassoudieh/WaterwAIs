#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include "variable.h"
#include <QMap>
#include <QString>

enum class object_type {node, link, entity};

class VariableList: public QMap<QString, Variable>
{
public:
    VariableList();
    VariableList& operator=(const VariableList& other);
    virtual ~VariableList();
    VariableList(const VariableList& other);
    VariableList(const QJsonObject& qjobject);
    QString IconFileName() {return iconfilename;}
    void SetIconFileName(const QString &icn ) {iconfilename = icn;}
    object_type ObjectType() {return Object_Type;}
private:
    QString iconfilename;
    object_type Object_Type;
};

#endif // VARIABLELIST_H
