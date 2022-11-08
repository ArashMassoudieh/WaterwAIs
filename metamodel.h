#ifndef METAMODEL_H
#define METAMODEL_H

#include <QString>
#include <variablelist.h>

//This class contains the information about all types of nodes and links that can be used in the model

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
