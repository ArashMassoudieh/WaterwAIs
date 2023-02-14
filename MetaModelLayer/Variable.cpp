#include "Variable.h"
#include <QJsonObject>
#include <QJsonValue>

#include <Common/qstr_unordered_map.h>
#include <cmath>




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

QString processValueUnit(QStringView unit_str) {
    static auto unit_map = []() {
        auto umap = qstr_unordered_map<QString>{};

        // Converting units from model to something more readable
        
        // Using superscript 2 for ~^2
        umap["m~^2"] = "m" + QString::fromWCharArray(L"\u00B2"); 

        return umap;
    }();
    
    if (auto found = unit_map.find(unit_str); found != unit_map.end())
        return found->second;

    return unit_str.toString();
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
    value_unit_.clear();

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
        auto value = std::get<double>(value_);
        auto integr = 0.0;

        auto float_part = std::modf(value, &integr);
        auto precision  = float_part == 0.0 ? 0 : 2;

        return QString::number(value, 'f', precision);
    }
    
    if (isTimeSeries()) {
        // get path to the CSV file for time series
        return std::get<QString>(value_);
    } else if (isString()) {
        return std::get<QString>(value_);
    }
    
    return {};
}

QString Variable::presentationValue() const {
    if (isTimeSeries()) {
        auto value = std::get<QString>(value_);
        return !value.isEmpty() ? "time series..." : "";
    }

    if (isNumeric() && !value_unit_.isEmpty()) {
        auto val_str = toString();

        val_str += " " + value_unit_;
        return val_str;
    }
    return toString();
}

void Variable::fromString(QStringView value) {
    if (isNumeric()) {
        if (!value.isEmpty() && value.back() == ']') {
            // We have units
            auto parts = QStringView{value.data(), value.size() - 1}.split('[');

            if (parts.size() > 1) {
                value_      = parts[0].toDouble();
                value_unit_ = processValueUnit(parts[1].toString());
            }
        } else
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
