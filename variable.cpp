#include "variable.h"
#include <QJsonObject>
#include <QJsonValue>

Variable::Variable()
{

}


Variable& Variable::operator=(const Variable& other)
{
    Type = other.Type;
    time_series = other.time_series;
    numeric_value = other.numeric_value;
    string_value = other.string_value;
    timeseries_filename = other.timeseries_filename;
    return *this;
}

Variable::~Variable()
{

}
Variable::Variable(const Variable& other)
{
    Type = other.Type;
    time_series = other.time_series;
    numeric_value = other.numeric_value;
    string_value = other.string_value;
    timeseries_filename = other.timeseries_filename;
}
Variable::Variable(const QJsonObject& qjobject)
{
    QString TypeString = qjobject.value("type").toString();
    if (TypeString == "value")
    {
        Type = variable_type::value;
    }
    else if (TypeString == "timeseries")
    {
        Type = variable_type::timeseries;
    }
    else if (TypeString == "string")
    {
        Type = variable_type::string;
    }
    QString RoleString = qjobject.value("role").toString();
    if (RoleString == "input")
    {
        Role = role::input;
    }
    else if (RoleString == "output")
    {
        Role = role::output;
    }
}

//This is for model layer data
Variable::Variable(const QString &objectType, const QJsonObject& qjobject)
{
    //QString TypeString = qjobject.value(objectType).toString();
    QString TypeString = objectType;
    if (TypeString == "x" || TypeString == "y")
    {
        Type = variable_type::value;
    }
    else if (TypeString == "timeseries")
    {
        Type = variable_type::timeseries;
    }
    else if (TypeString == "area" || TypeString == "name" || TypeString == "mail" || TypeString == "slope")
    {
        Type = variable_type::string;
    }
}


QString Variable::GetValue()
{
    if (Type==variable_type::value)
    {
        return QString::number(numeric_value);
    }
    else if (Type==variable_type::timeseries)
    {
        return timeseries_filename;
    }
    else if (Type==variable_type::string)
    {
        return string_value;
    }
    else
    {
        return "";
    }
}

void Variable::SetValue(const QString &value)
{
    if (Type==variable_type::value || Type==variable_type::constant)
    {
        numeric_value=value.toDouble();
    }
    else if (Type==variable_type::timeseries || Type==variable_type::prec_timeseries)
    {
        timeseries_filename = value;
    }
    else if (Type==variable_type::string)
    {
        string_value = value;
    }
    else
    {
        string_value = value;
    }
}
