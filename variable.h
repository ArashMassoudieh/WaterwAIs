#ifndef VARIABLE_H
#define VARIABLE_H
#include <QJsonDocument>
#include <BTC.h>


enum class variable_type {constant, value, timeseries, prec_timeseries, string, not_assigned};
enum class role {output, input, none};
class Variable
{
public:
    Variable();
    Variable& operator=(const Variable& other);
    virtual ~Variable();
    Variable(const Variable& other);
    Variable(const QJsonObject& qjobject);
    Variable(const QString &objectType, const QJsonObject& qjobject);
    QString GetValue();
    void SetTimeSeries(const QString &name) {timeseries_filename = name;}
    void SetRole(const role &rl) {Role = rl;}
    void SetValue(const QString &value) {string_value = value;}
    void SetValue(const double &value) {numeric_value = value;}
    void SetType(const variable_type &type) {Type = type;}
private:
    variable_type Type = variable_type::not_assigned;
    double numeric_value = 0;
    CTimeSeries<double> time_series;
    QString timeseries_filename;
    QString string_value;
    role Role = role::none;

};

#endif // VARIABLE_H
