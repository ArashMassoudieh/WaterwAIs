#ifndef LAYERMETAMODELITEM_H_8ACEBEDC6E080732
#define LAYERMETAMODELITEM_H_8ACEBEDC6E080732

#include <Layer/LayerGraphicsItem.h>
#include "MetaLayerModelItem.h"

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MetaLayerItem
//
// This class represents a base class for Meta Model layer graphic items
// For example, Node and Link MetaModel layer graphic items are derived
// from it.

class MetaLayerItem: public LayerGenericItem {
public:
    using ModelItem = MetaLayerModelItems::Item;

    MetaLayerItem(const LayerGraphicsSettings& gsettings,
        ModelItem& model_item);
        
    // Checks if some graphics item is a layer meta item and returns casted
    // pointer if it is the case.
    static MetaLayerItem* item_cast(QGraphicsItem* item);

    // Properties
    const VariableMap& properties() const { return model_item_.properties(); }

    // Model item
    const ModelItem& modelItem() const { return model_item_; }

protected:
    // Meta model data item for this graphics object.
    ModelItem& model_item_;

};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // LAYERMETAMODELITEM_H_8ACEBEDC6E080732