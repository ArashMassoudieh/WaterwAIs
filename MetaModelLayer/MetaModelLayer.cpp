
#include "MetaModelLayer.h"
#include "MetaLayerModel.h"

#include <QJsonObject>
#include <QGraphicsScene>

namespace WaterwAIs {

namespace {
    constexpr auto meta_layer_z_value = 40000;
} // anonymous

//////////////////////////////////////////////////////////////////////////
// MetaModelLayer

MetaModelLayer::MetaModelLayer(LayerSceneInterface* scene,
    QStringView component_json_file, QStringView json_file) : Layer{scene} {

    // We use a fixed z-value for the Meta model layer.
    z_value_ = meta_layer_z_value;
    options_.setFlag(Option::FixedZValue);

    gsettings_.brush = QBrush{};

    if (!json_file.isEmpty()) {
        // We have a JSON file to build the feature model for the layer.
        auto meta_layer_model = std::make_shared<MetaLayerModel>();        

        // Let's build the component meta model for the layer.
        if (!component_json_file.isEmpty())
            meta_layer_model->getComponentMetaModel(component_json_file);
        
        model_ = meta_layer_model;
        getFromJson(json_file);
    }
}

bool MetaModelLayer::zOrderMovable() {
    // Meta model layer should keep its z order and it may not be moved in the
    // layer list.
    return false;
}


} // namespace WaterwAIs