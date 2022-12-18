#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include "variable.h"
#include <QMap>
#include <QString>

enum class object_type {node, link, entity};

struct NameValuePair
{
    QString Name;
    Variable *Var = nullptr;
};

class VariableList: public QMap<QString, Variable>
{
public:
    VariableList();
    VariableList& operator=(const VariableList& other);
    virtual ~VariableList();
    VariableList(const VariableList& other);
    VariableList(const QString &objectType, const QJsonObject& qjobject);
    VariableList(const QJsonObject& qjobject);
    QString IconFileName() {return iconfilename;}
    void SetIconFileName(const QString &icn ) {iconfilename = icn;}
    object_type ObjectType() const {return Object_Type;}
    void SetObjectType(object_type ObjType) {Object_Type = ObjType;}
    QString ComponentType() {return component_type;}
    void SetComponentType(const QString &componentType) {component_type = componentType;}
    bool SetValue(const QString &VariableName, const QString &Value);
    bool AddXYNameVariables();
    bool AddNameVariable();
    NameValuePair operator[](int i);
    Variable& operator[](const QString name);

private:
    QString iconfilename;
    object_type Object_Type;
    QString component_type;
};

#endif // VARIABLELIST_H
