
#include "MetaLayerModel.h"
#include "MetaLayerModelItem.h"

#include "NodeLayerItem.h"
#include "LinkLayerItem.h"

namespace WaterWays {
namespace MetaLayerModelItems {

namespace {
using Type = Variable::Type;

// Returns property value type from property name 
// 
// TODO:  Put it in some kind of table.
Variable::Type typeFromPropName(QStringView prop_name) {    
    auto type = Type::NotAssigned;

    // Auxiliary type strings
    if (prop_name == u"x" || prop_name == u"y") {
        type = Type::Value;
    } else if (prop_name == u"area" || prop_name == u"name" ||
        prop_name == u"mail" || prop_name == u"slope") {
        type = Type::String;
    }
    return type;
}

// Returns property value type from property JSON value.
Variable::Type typeFromValue(const QJsonValue& json_value) {
    auto type = Type::String;

    // Check for double type
    auto ok = false;
    auto value = json_value.toString().toDouble(&ok);

    if (ok)
        type = Type::Value;

    // TODO: Add mode type checks to convert property values into relevant 
    //types.

    return type;
}

// Return property type based on property name and JSON value
Variable::Type typeFromProperty(QStringView prop_name, 
    const QJsonValue& json_value) {    

    // Check property name
    auto type = typeFromPropName(prop_name);
    if (type != Type::NotAssigned)
        return type;

    // Check property value
    type = typeFromValue(json_value);
    if (type != Type::NotAssigned)
        return type;

    return Type::String;
}

} // anonymous

//////////////////////////////////////////////////////////////////////////
// Item

Item::Item(QStringView name, MetaComponentItem& component, MetaLayerModel& model)
    : name_{name.toString()}, component_{component}, model_{model} {
    // Preset "name" property as each item is supposed to have name.
    properties_.set(u"name", {Variable::Type::String});
}

Item::Ptr Item::create(QStringView name, MetaComponentItem& component,
    MetaLayerModel& model) {
    auto type = component.type();

    switch (type) {
    case MetaComponentItem::Type::Node:
        return std::make_unique<NodeItem>(name, component, model);

    case MetaComponentItem::Type::Link:
        return std::make_unique<LinkItem>(name, component, model);
        
    case MetaComponentItem::Type::Entity:
        // TBD.
        break;
    default:
        break;
    }
    return {};
}

void Item::getFromJson(const QJsonValue& json_value) {
    auto json_object = json_value.toObject();

    // Item properties
    for (auto& property : json_object.keys()) {
        auto value = json_object.value(property);

        auto prop_value = Variable{typeFromProperty(property, value)};
        prop_value.fromString(value.toString());

        // We set only properties that match component's meta model item.
        auto property_set = properties_.setIfExistInOtherMap
            (component_.properties(), property, prop_value);

        // or properties that have been already preset.
        if (!property_set)
            property_set = properties_.setIfExist(property, prop_value);

        qDebug() << "[" << MetaComponentItem::typeToSting(type()) <<  
            "] item, [set " << property_set << "] property=" <<
            property << ", value =" << value;

        onProperty(property, value);
    }
}

//////////////////////////////////////////////////////////////////////////
// NodeItem

namespace {
    
} // anonymous

NodeItem::NodeItem(QStringView name, MetaComponentItem& component,
    MetaLayerModel& model)
    : Item{name, component, model} {

    // Preset geometry-related properties for the Node
    properties_.set(u"x", {Variable::Type::Value});
    properties_.set(u"y", {Variable::Type::Value});
}

void NodeItem::getFromJson(const QJsonValue& json_value) {
    Item::getFromJson(json_value);

    // Coordinates
    auto x = properties_[u"x"].get<double>();
    auto y = properties_[u"y"].get<double>();
    coordinates_ = {x, y};
}

void NodeItem::addGraphicsItems(const LayerGraphicsSettings& gsettings,
    LayerGraphicsItems& items) {
    auto node = new NodeLayerItem{gsettings, *this};

    // Add the node item to the graphics items collection.
    items.addItem(node);

    // Store the node in the node map.
    auto inserted = model_.nodesMap().try_emplace(name_, node).second;

    if (!inserted) {
        qDebug() << "Node graphic item for name: " << name_
            << "already exist in the map";
    }
}

//////////////////////////////////////////////////////////////////////////
// LinkItem

void LinkItem::onProperty(QStringView name, const QJsonValue& json_value) {
    // Source/Destination
    if (name == u"from")
        source_ = json_value.toString();
    else if(name == u"to")
        destination_ = json_value.toString();
}


void LinkItem::addGraphicsItems(const LayerGraphicsSettings& gsettings,
    LayerGraphicsItems& items) {
    if (source_.isEmpty()) {
        qDebug() << "LinkItem, source node is empty";
        return;
    }

    if (destination_.isEmpty()) {
        qDebug() << "LinkItem, destination node is empty";
        return;
    }    

    auto source_node      = model_.getNode(source_);
    auto destination_node = model_.getNode(destination_);    

    auto link = new LinkLayerItem{gsettings, *this, source_node,
        destination_node};

    // Add link to the graphics items collection.
    items.addItem(link);

    //link->adjust();
}


} // namespace MetaLayerModelItems
} // namespace WaterWays