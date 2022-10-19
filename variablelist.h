#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include "variable.h"
#include <QMap>
#include <QString>

class VariableList: public QMap<QString, Variable>
{
public:
    VariableList();
    VariableList& operator=(const VariableList& other);
    virtual ~VariableList();
    VariableList(const VariableList& other);
    VariableList(const QJsonObject& qjobject);
};

#endif // VARIABLELIST_H
