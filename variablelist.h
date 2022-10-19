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
    QString IconFileName() {return iconfilename;}
    void SetIconFileName(const QString &icn ) {iconfilename = icn;}
private:
    QString iconfilename;
};

#endif // VARIABLELIST_H
