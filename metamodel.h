#ifndef METAMODEL_H
#define METAMODEL_H

#include <QString>
#include <variablelist.h>

class MetaModel: public QMap<QString,VariableList>
{
public:
    MetaModel();
    MetaModel& operator=(const MetaModel& other);
    virtual ~MetaModel();
    MetaModel(const MetaModel& other);
    MetaModel(QJsonDocument& qjobject);
};

#endif // METAMODEL_H
