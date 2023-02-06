#include "Variable.h"
#include <QJsonObject>
#include <QJsonValue>

namespace WaterwAIs {

namespace {

// Converts string to Variable::Type.
Variable::Type to_type(QStringView type_string) {
    using Type = Variable::Type;
    auto type = Type::NotAssigned;

    // Major type strings
    if (type_string == u"value") {
        type = Type::Value;
    } else if (type_string == u"timeseries") {
        type = Type::TimeSeries;
    } else if (type_string == u"string") {
        type = Type::String;
    }    
    return type;
}

} // anonymous

//////////////////////////////////////////////////////////////////////////
// Variable

Variable::Variable(const QJsonObject& json_object) {
    getFromJsonObject(json_object);
}

//This is for model layer data
Variable::Variable(QStringView type_string): type_{to_type(type_string)} {    
}

void Variable::init() {
    // Initializing value from type
    value_ = {};

    switch (type_) {
    case Type::NotAssigned:
        break;

    case Type::Constant:
    case Type::Value:
        value_ = 0.0;
        break;

    case Type::TimeSeries:
        break;

    case Type::PrecTimeSeries:
        break;

    case Type::String:
        value_ = QString{};
        break;

    default:
        break;
    }
}

void Variable::getFromJsonObject(const QJsonObject& json_object) {
    auto type_string = json_object.value("type").toString();
    type_ = to_type(type_string);

    auto role_string = json_object.value("role").toString();
    if (role_string == "input") {
        role_ = Role::Input;
    } else if (role_string == "output") {
        role_ = Role::Output;
    }
    init();
}

QString Variable::toString() const{
    if (isNumeric()) {
        return QString::number(std::get<double>(value_), 'f', 2);
    } else if (isTimeSeries()) {
        // get path to the CSV file for time series
        return std::get<QString>(value_);
    } else if (isString()) {
        return std::get<QString>(value_);
    }
    return {};
}

QString Variable::presentationValue() const {
    if (isTimeSeries())
        return "time series";

    return toString();
}

void Variable::fromString(QStringView value) {
    if (isNumeric()) {
        value_ = value.toDouble();
    } else if (isTimeSeries()) {
        value_ = value.toString();
    } else if (isString()) {
        value_ = value.toString();
    } else {
        // Store values for unknown type as strings
        value_ = value.toString();
    }
}

} // namespace WaterwAIs
