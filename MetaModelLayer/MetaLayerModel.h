#ifndef METALAYERMODEL_H_8139F46A36E06E32
#define METALAYERMODEL_H_8139F46A36E06E32

#include <Layer/LayerModel.h>
#include "MetaComponentItem.h"

#include <qstr_unordered_map.h>
#include <map>

namespace WaterwAIs {

class NodeLayerItem;

namespace MetaLayerModelItems {
class NodeItem;
class LinkItem;
class GenericItem;
}

//////////////////////////////////////////////////////////////////////////
// MetaLayerModel
// 
// This class contains the information about all types of nodes and links
// that can be used in the model.

//////////////////////////////////////////////////////////////////////////
// MetaLayerModel

class MetaLayerModel: public LayerModel {
    Q_OBJECT
public:
    using NodeItem    = MetaLayerModelItems::NodeItem;
    using LinkItem    = MetaLayerModelItems::LinkItem;
    using GenericItem = MetaLayerModelItems::GenericItem;

    using NodeItemPtr    = std::unique_ptr<NodeItem>;
    using LinkItemPtr    = std::unique_ptr<LinkItem>;
    using GenericItemPtr = std::unique_ptr<GenericItem>;

    using LayerNodeItemMap = qstr_unordered_map<NodeLayerItem*>;
    using GenericItemMap   = std::map<QString, GenericItem*, std::less<>>;

    MetaLayerModel();
    virtual ~MetaLayerModel();    

    // Builds Meta model for components from JSON file
    void getComponentMetaModel(QStringView json_file);

    // Map of Node graphics items
          LayerNodeItemMap& nodesMap()       { return node_map_; }
    const LayerNodeItemMap& nodesMap() const { return node_map_; }

    // Get Node
    const NodeLayerItem* getNode(QStringView node_name) const;

    // Map of Generic (no type) model items
          GenericItemMap& genericItemMap()       { return generic_item_map_; }
    const GenericItemMap& genericItemMap() const { return generic_item_map_; }

    // Model-specific Node and Link item creator functions allowing to create
    // node and link items with custom properties (i.e. special drawing based
    // on name).
    NodeItemPtr    createNode   (QStringView name, MetaComponentItem& component);
    LinkItemPtr    createLink   (QStringView name, MetaComponentItem& component);
    GenericItemPtr createGeneric(QStringView name, MetaComponentItem& component);

protected:
    // Fills Meta model for components from JSON doc
    void getComponentMetaModel(const QJsonDocument& json_doc);

    // Notification that model has been downloaded.
    void onModelDownloaded(QJsonDocument&& json_doc) override;

    // Fills the model from some JSON document
    void getFromJsonDocument(const QJsonDocument& json_doc) override;

    // Allows to handle special meta model items like name or icon.
    bool handleItem(QStringView name, const QJsonValue& value);

private:    
    // This function is for collecting meta data and comparing with model layer
    // data.
    void addMetaModel(const QJsonDocument& json_doc);
    
    // Meta model component item map, component type is the key.
    qstr_unordered_map<MetaComponentItem> component_map_;
    bool components_ready_ = false;

    // Map containing Node graphics items, needed for links between nodes.
    LayerNodeItemMap node_map_;

    // Map containing generic items (with no type)
    GenericItemMap generic_item_map_;

    QJsonDocument json_doc_;
};

} // namespace WaterwAIs


//////////////////////////////////////////////////////////////////////////
#endif // METALAYERMODEL_H_8139F46A36E06E32

