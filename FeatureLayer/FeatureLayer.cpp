
#include "FeatureLayer.h"
#include <QJsonObject>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// FeatureLayerModel

void FeatureLayerModel::getFromJsonDocument(const QJsonDocument& json_doc) {
    auto json_object = json_doc.object();

    for(auto& key : json_object.keys()) {
        auto value = json_object.value(key);
        qDebug() << "Key = " << key << ", Value = " << value.toString();
    }

    if (json_object.contains("name")) {
        auto name = json_object.value("name").toString();
        setName(name);
    }

    if (json_object.contains("icon")) {
        auto icon_url = json_object.value("icon").toString();
        getIcon(icon_url);
    }

    auto json_features = json_object.value("features").toArray();

    feature_type_ = FeatureType::Unknown;

    for (auto&& json_feature : json_features) {
        auto value = json_feature.toObject();
        auto geometry = value["geometry"].toObject();
        // qDebug()<<"Geometry: " <<geometry;
        
        auto coordinates = geometry["coordinates"];
        auto type = geometry["type"].toString();

        // qDebug() << "Key = " << i << ", Coordinates = " <<
        // coordinates << ", Type = " << type;        

        if (auto feature = FeatureModelItem::create(type); feature) {
            if (feature_type_ == FeatureType::Unknown) {
                // Setting layer's feature type from the first feature.
                feature_type_ = feature->type();
            }
            
            if (feature->type() == feature_type_) {
                // Layer has feature type set, and our feature matches it, so
                // we can add it.
                feature->getFromJson(coordinates);
                
                // Storing the feature item in the model.                
                items_.emplace_back(std::move(feature));
            } else {
                // !!! Layer has a different feature type, so we should skip
                // the feature.
                qDebug() <<
                    "Wrong feature type: " << static_cast<int>(feature->type()) <<
                    " for layer type: " << static_cast<int>(feature_type_);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// FeatureLayer

FeatureLayer::FeatureLayer(LayerSceneInterface* scene, const QColor& color,
    QStringView json_file, Options options)
    : Layer{scene, nullptr, color, options} {
    if (!json_file.isEmpty()) {
        // We have a JSON file to build the feature model for the layer.
        model_ = std::make_shared<FeatureLayerModel>();
        getFromJson(json_file);
    }
}


} // namespace WaterwAIs