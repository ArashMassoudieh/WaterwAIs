#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include "variable.h"
#include <QMap>
#include <QString>

class VariableList: public QMap<QString, Variable>
{
public:
    VariableList();
};

#endif // VARIABLELIST_H
