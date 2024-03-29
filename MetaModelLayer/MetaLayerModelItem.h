#ifndef METALAYERMODELITEM_H_8E6BAD7E50C75355
#define METALAYERMODELITEM_H_8E6BAD7E50C75355

#include <Layer/LayerModelItem.h>
#include "MetaComponentItem.h"

namespace WaterwAIs {

class MetaLayerModel;
class NodeLayerItem;
class LinkLayerItem;

namespace MetaLayerModelItems {

// The classes here represent "elements" or data items for the Meta Model layer
// which are used to construct Meta Model layer graphic items.

//////////////////////////////////////////////////////////////////////////
// Item

class Item: public LayerModelItem {
public:
    using Type = MetaComponentItem::Type;
    using GraphicsItems = LayerModelItem::GraphicsItems;
    using Ptr = std::unique_ptr<Item>;

    Item(QStringView name, MetaComponentItem& component, MetaLayerModel& model);

    // Name
    QStringView name() const 
        { return display_name_.isEmpty() ? name_ : display_name_; }

    // Type
    Type type() const { return component_.type(); }

    // Component
    MetaComponentItem& component() { return component_; }
    const MetaComponentItem& component() const { return component_; }

    // Fills the layer item from the JSON value
    void getFromJson(const QJsonValue& json_value) override;

    // Creator function
    static Ptr create(QStringView name, MetaComponentItem& component,
        MetaLayerModel& model);

    // Properties
    const VariableMap& properties() const { return properties_; }

    // Tooltip
    virtual QString toolTip() const;

    // Model
    MetaLayerModel& model() { return model_; }

protected:
    bool preProcessProperty(QStringView name, const QJsonValue& json_value);

    virtual bool handleProperty(QStringView /*name*/,
        const QJsonValue& /*json_value*/) {
        // Allows derived classes to preprocess and consume the property
        // instead of putting it into the properties map.
        return false; /* not processed */
    }

    virtual void onProperty(QStringView /*name*/, 
        const QJsonValue& /*json_value*/) {}

    QString            name_;
    QString            display_name_;
    MetaComponentItem& component_;
    VariableMap        properties_;
    MetaLayerModel&    model_;
};


//////////////////////////////////////////////////////////////////////////
// NodeItem

class NodeItem: public Item {
public:
    NodeItem(QStringView name, MetaComponentItem& component, MetaLayerModel& model);

    // Fills the layer item from the JSON value
    void getFromJson(const QJsonValue& json_value) override;

    // Allows the layer item to provide graphics items for presentation.
    // The function provides caller's "pen" with color and other attributes,
    // which may be applied to the item's graphics items.
    void addGraphicsItems(const LayerGraphicsSettings& gsettings,
        LayerGraphicsItems& items) override;

    const QPointF coordinates() const { return coordinates_; }

    // Width/Height for display in the Map view
    double width () const { return width_ > 0  ? width_  : component_.width(); }
    double height() const { return height_ > 0 ? height_ : component_.height(); }

    // Creates graphical layer item for Node.
    virtual NodeLayerItem* createLayerItem
        (const LayerGraphicsSettings& gsettings);

protected:
    bool handleProperty(QStringView name, const QJsonValue& json_value) override;

private:
    QPointF coordinates_;
    double  width_  = 0.0;
    double  height_ = 0.0;
};


//////////////////////////////////////////////////////////////////////////
// LinkItem

class LinkItem: public Item {
public:
    LinkItem(QStringView name, MetaComponentItem& component, MetaLayerModel& model):
        Item{name, component, model} {}

    // Allows the layer item to provide graphics items for presentation.
    // The function provides caller's "pen" with color and other attributes,
    // which may be applied to the item's graphics items.
    void addGraphicsItems(const LayerGraphicsSettings& gsettings,
        LayerGraphicsItems& items) override;

    QStringView source     () const { return source_; }
    QStringView destination() const { return destination_; }

    // Creates graphical layer item for Link.
    virtual LinkLayerItem* createLayerItem
        (const LayerGraphicsSettings& gsettings, NodeLayerItem* source,
            NodeLayerItem* destination);

protected:
    void onProperty(QStringView name, 
        const QJsonValue& json_value) override;

private:
    QString source_;
    QString destination_;
};


//////////////////////////////////////////////////////////////////////////
// GenericItem

class GenericItem: public Item {
public:
    GenericItem(QStringView name, MetaComponentItem& component,
        MetaLayerModel& model):
        Item{name, component, model} {}

    void addGraphicsItems(const LayerGraphicsSettings&,
        LayerGraphicsItems&) override { /* No graphical items */ }

private:
};



} // namespace MetaLayerModelItems
} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // METALAYERMODELITEM_H_8E6BAD7E50C75355