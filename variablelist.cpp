#include "variablelist.h"

VariableList::VariableList():QMap<QString,Variable>()
{

}


VariableList& VariableList::operator=(const VariableList& other)
{
    QMap<QString,Variable>::operator=(other);
}

VariableList::~VariableList()
{

}
VariableList::VariableList(const VariableList& other):QMap<QString,Variable>(other)
{

}
VariableList::VariableList(QJsonObject& qjobject):QMap<QString,Variable>()
{

}
