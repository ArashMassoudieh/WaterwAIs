#include "variable.h"

Variable::Variable()
{

}


Variable& Variable::operator=(const Variable& other)
{
    Type = other.Type;
    time_series = other.time_series;
    numeric_value = other.numeric_value;
    string_value = other.string_value;
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
}
Variable::Variable(QJsonObject& qjobject)
{

}
QString Variable::GetValue()
{

}
