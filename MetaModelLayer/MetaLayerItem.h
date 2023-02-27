#ifndef LAYERMETAMODELITEM_H_8ACEBEDC6E080732
#define LAYERMETAMODELITEM_H_8ACEBEDC6E080732

#include <Layer/LayerGraphicsItem.h>
#include "MetaLayerModelItem.h"

#include <vector>
#include <memory>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MetaLayerItemLink

class MetaLayerItem;

class MetaLayerItemLink {
public:
    using Ptr = std::shared_ptr<MetaLayerItemLink>;

    MetaLayerItemLink(MetaLayerItem& source, MetaLayerItem& destination,
        MetaLayerItem& link): source_{source}, destination_{destination}
        , link_{link} {
    }

    MetaLayerItem& source     () { return source_; }
    MetaLayerItem& destination() { return destination_; }
    MetaLayerItem& link       () { return link_; }

private:
    MetaLayerItem& source_;
    MetaLayerItem& destination_;
    MetaLayerItem& link_;
};

//////////////////////////////////////////////////////////////////////////
// MetaLayerItem
//
// This class represents a base class for Meta Model layer graphic items
// For example, Node and Link MetaModel layer graphic items are derived
// from it.

class MetaLayerItem: public LayerGenericItem {
public:
    using ModelItem = MetaLayerModelItems::Item;
    using ItemLinks = std::vector<MetaLayerItemLink::Ptr>;

    static constexpr double item_zvalue = 40000;

    MetaLayerItem(const LayerGraphicsSettings& gsettings,
        ModelItem& model_item);
        
    // Checks if some graphics item is a layer meta item and returns casted
    // pointer if it is the case.
    static MetaLayerItem* item_cast(QGraphicsItem* item);

    // Properties
    const VariableMap& properties() const { return model_item_.properties(); }

    // Model item
    const ModelItem& modelItem() const { return model_item_; }

    // Links
    void addLink(MetaLayerItemLink::Ptr link) { links_.emplace_back(link); }

    const ItemLinks& links() const { return links_; }

    // Highlighting
    void setHighlighted(bool highlighted) { highlighted_ = highlighted; }
    bool isHighlighted() const { return highlighted_; }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

    // Meta model data item for this graphics object.
    ModelItem& model_item_;

    // Item links
    ItemLinks links_;

    bool highlighted_ = false;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // LAYERMETAMODELITEM_H_8ACEBEDC6E080732