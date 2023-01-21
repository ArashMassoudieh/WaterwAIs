
#include "MetaModelLayer.h"
#include "MetaLayerModel.h"

#include <QJsonObject>
#include <QGraphicsScene>

namespace WaterWays {

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

} // namespace WaterWays