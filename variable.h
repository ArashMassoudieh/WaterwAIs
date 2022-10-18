#ifndef VARIABLE_H
#define VARIABLE_H
#include <QJsonDocument>
#include <BTC.h>


enum class variable_type {constant, value, timeseries, prec_timeseries, string, not_assigned};

class Variable
{
public:
    Variable();
    Variable& operator=(const Variable& other);
    virtual ~Variable();
    Variable(const Variable& other);
    Variable(QJsonObject& qjobject);
    QString GetValue();
private:
    variable_type Type;
    double numeric_value;
    CTimeSeries<double> time_series;
    QString string_value;

};

#endif // VARIABLE_H
