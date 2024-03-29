#ifndef VARIABLE_H_89744759ADDA9F48
#define VARIABLE_H_89744759ADDA9F48

#include <QJsonDocument>

#include <variant>
#include <qstr_unordered_map.h>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// Variable

class Variable {
public:
    enum class Type {
        NotAssigned = 0,
        Constant,
        Value,
        TimeSeries,
        PrecTimeSeries,
        String
    };

    enum class Role { 
        None,
        Output,
        Input
    };
    
    Variable(Type type = Type::NotAssigned, QStringView value = {},
        QStringView display_name = {},
        QStringView description = {})
        : type_{type}, display_name_{display_name.toString()}
        , description_ {description.toString()} {
        init();
        if (!value.isNull())
            fromString(value);
    }

    Variable(const QJsonObject& json_object);
    Variable(QStringView type_str);
    
    void getFromJsonObject(const QJsonObject& json_object);
   
    // Type
    Type type() const { return type_; }
    void setType(const Type& type) { type_ = type; init(); }
    
    // Type checking shortcuts
    bool isNumeric() const
        { return (type_ == Type::Value || type_ == Type::Constant); }

    bool isString() const { return type_ == Type::String; }

    bool isTimeSeries() const
        { return  type_ == Type::TimeSeries || type_ == Type::PrecTimeSeries; }

    bool isNotAssigned() const { return type_ == Type::NotAssigned; }
    bool isAssigned() const { return !isNotAssigned(); }

    // Role
    Role role() const { return role_; }
    void setRole(const Role& rl) { role_ = rl; }

    // Value
    // Gets/Sets using string representation of the value
    QString toString() const;
    void fromString(QStringView value);
    
    // Display name
    QString displayName() const { return display_name_; }

    // Description
    QString description() const { return description_; }

    // Value unit
    QString valueUnit() const { return value_unit_; }

    // Gets variable value string for 'presentation' - it can be different
    // from a real string value thus hiding it from the user.
    QString presentationValue() const;
    

    void setValue(double value) { 
        if (isNumeric())
            value_ = value;
    }

    void setTimeSeries(QStringView name) {
        if (isTimeSeries())
            value_ = name.toString();
    }
    
    template <typename T>
    const T& get() { return std::get<T>(value_); }

private:
    void init();

    Type type_ = Type::NotAssigned;
    Role role_ = Role::None;

    std::variant<double, QString> value_;

    QString display_name_; // Name for display
    QString description_;  // Variable description.
    QString value_unit_;   // Specifies dimensional unit for 'Value' type
};

//////////////////////////////////////////////////////////////////////////
// VariableMap
//

class VariableMap {
public:
    // Sets variable in the map regardless whether it exists already or not.
    void set(QStringView name, const Variable& value = {})
        { variable_map_[name.toString()] = value; }

    // Sets variable if it exists
    bool setIfExist(QStringView name, const Variable& value = {}) {
        if (auto found = variable_map_.find(name.toString());
            found != variable_map_.end()) {
            // Found our property, so we can set it.
            found->second = value;
            return true;
        }
        return false;
    }

    // Sets variable if it exists in the other map
    bool setIfExistInOtherMap(const VariableMap& other_map, QStringView name,
        QStringView value = {}) {
        
        if (auto var = other_map.get(name); var) {
            // Import type from the variable with the same name from the other
            //map.
            set(name, Variable{var->type(), value,
                var->displayName(), var->description()});

            return true;
        }
        return false;
    }

    void setIfNotExist(QStringView name, const Variable& value = {})
        { variable_map_.try_emplace(name.toString(), value); }

    bool contains(QStringView name) const
        { return get(name) != nullptr; }

    // Get functions
    Variable* get(QStringView name) {
        if (auto found = variable_map_.find(name.toString());
            found != variable_map_.end()) {
            return &found->second;
        }
        return {};
    }

    // Constant version
    const Variable* get(QStringView name) const {
        if (auto found = variable_map_.find(name.toString());
            found != variable_map_.end()) {       
            return &found->second;
        }
        return {};
    }

    // Provides reference to the stored variable or create a new one if it
    // doesn't exists.
    Variable& operator[](QStringView name) {
        return variable_map_[name.toString()];
    }

    // Info functions
    size_t size() const { return variable_map_.size(); }
    bool empty () const { return variable_map_.empty(); }

    // Map access (to iterate over variables etc.)
    const qstr_unordered_map<Variable>& vars() const { return variable_map_; }

private:
    qstr_unordered_map<Variable> variable_map_;
};


} //namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // VARIABLE_H_89744759ADDA9F48
