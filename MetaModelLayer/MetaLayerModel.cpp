
#include "MetaLayerModel.h"
#include "MetaLayerModelItem.h"

#include <Application/FileNameProcessor.h>

#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "NodeLayerItem.h"

namespace WaterwAIs {

using namespace MetaLayerModelItems;

//////////////////////////////////////////////////////////////////////////
// MetaModel

MetaLayerModel::MetaLayerModel() {
}

MetaLayerModel::~MetaLayerModel() {
}

void MetaLayerModel::getComponentMetaModel(QStringView json_file) {
    components_ready_ = false;

    downloadJson(WW_HOST_PATH(json_file), 
        [this](auto result, auto&& json_doc) {
            component_map_.clear();

            if (!result) {
                qDebug() << "Failed to load component model";
                return;
            }
            getComponentMetaModel(json_doc);
        });
}

void MetaLayerModel::getComponentMetaModel(const QJsonDocument& json_doc) {    
    auto json_object = json_doc.object();

    for (auto& key : json_object.keys()) {
        auto value = json_object.value(key);

        // Check for special items, like name or icon
        if (handleItem(key, value))
            continue;

        auto properties = value.toObject();
        component_map_.emplace(key, properties);
    }
    components_ready_ = true;

    if (model_downloaded_) {
        // Our component model was downloaded after the main model was
        // downloaded. So, now it is time to load the main model.
        LayerModel::onModelDownloaded(std::move(json_doc_));
    }
}

bool MetaLayerModel::handleItem(QStringView name, const QJsonValue& value) {
    // Handle special items    
    if (name == u"name") {
        // Name
        setName(value.toString());
        return true;
    } else if (name == u"icon") {
        // Icon
        auto icon_url = value.toString();
        getIcon(icon_url);
        return true;
    }    
    
    return false;
}


void MetaLayerModel::addMetaModel(const QJsonDocument& /*json_doc*/) {
    // This function is for collecting meta data and comparing with model layer
    // data, still working on it.
    // TBD.
}

void MetaLayerModel::onModelDownloaded(QJsonDocument&& json_doc) {
    if (!components_ready_) {
        // Component map is not ready yet, so let's store our model JSON doc
        // and use it when it is ready
        json_doc_ = std::move(json_doc);
        return;
    }

    // Components are ready, so we can load it from JSON.
    LayerModel::onModelDownloaded(std::move(json_doc));
}


void MetaLayerModel::getFromJsonDocument(const QJsonDocument& json_doc) {
    auto json_object = json_doc.object();

    for (auto& key : json_object.keys()) {
        auto item_value  = json_object[key];
        auto item_object = item_value.toObject();

        auto component_type = item_object["type"].toString();
        auto component = static_cast<MetaComponentItem*>(nullptr);

        if (auto found = component_map_.find(component_type); found != component_map_.end())
            component = &found->second;

        if (!component) {
            qDebug() << "Component: " << component_type << 
                " wasn't found in the Meta model";
            continue;
        }

        if (auto item = Item::create(key, *component, *this); item) {
            item->getFromJson(item_value);

            // Storing the items in the model making sure that the node items are
            // placed at the front, so their layer graphic items will be created
            // first and become available to the link graphic items.
            if (item->type() == MetaComponentItem::Type::Node)
                items_.emplace_front(std::move(item));
            else
                items_.emplace_back(std::move(item));
        }
    }
}

const NodeLayerItem* MetaLayerModel::getNode(QStringView node_name) const {
    if (auto search = node_map_.find(node_name.toString()); search != node_map_.end())
        return search->second;
    return {};
}


//////////////////////////////////////////////////////////////////////////
// Example of custom Node item drawing its name

/*
class CustomNodeLayerItem: public NodeLayerItem {
public:
    CustomNodeLayerItem(const LayerGraphicsSettings& gsettings, NodeItem& node_item):
        NodeLayerItem{gsettings, node_item} {
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) override {
        NodeLayerItem::paint(painter, option, widget);

        auto font = painter->font();
        font.setPixelSize(24);
        painter->setFont(font);

        painter->drawText(boundingRect(), Qt::AlignCenter, model_item_.name().toString());
    }
};


class CustomNodeItem: public NodeItem {
public:
    CustomNodeItem(QStringView name, MetaComponentItem& component, MetaLayerModel& model):
        NodeItem{name, component, model} {}

    NodeLayerItem* createLayerItem(const LayerGraphicsSettings& gsettings) override {
        return new CustomNodeLayerItem{gsettings, *this};
    }
};
*/

MetaLayerModel::NodeItemPtr MetaLayerModel::createNode(QStringView name,
    MetaComponentItem& component) {
    Q_UNUSED(name);
    Q_UNUSED(component);

    // Create custom Node objects here like:
    //if (name == u"subcatchment2")
    //    return std::make_unique<CustomNodeItem>(name, component, *this);

    // default Node item creation in the Item::create()
    return {};
}

MetaLayerModel::LinkItemPtr MetaLayerModel::createLink(QStringView name,
    MetaComponentItem& component) {
    Q_UNUSED(name);
    Q_UNUSED(component);

    // Create custom Link objects here like:
    // return std::make_unique<CustomLinkItem>(name, component, model);
    //

    // default Node item creation in the Item::create()
    return {};
}

} // namespace WaterwAIs
