
#include "LayersInfo.h"
#include "FileNameProcessor.h"

#include <Common/Downloader.h>

#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// FeatureLayerInfo

FeatureLayerInfo::FeatureLayerInfo(QStringView layer_name,
    const QJsonObject& json_object): name{layer_name.toString()} {

    for (auto& key : json_object.keys()) {
        auto value = json_object.value(key);

        if (key == "description")
            description = value.toString();
        else if (key == "url")
            json_file = value.toString();
        else if (key == "contours" && value.toString() == "true")
            uses_shapes = false;
        else if (key == "color")
            color = QColor{value.toString()};
    }
}


//////////////////////////////////////////////////////////////////////////
// MetaLayerInfo

void MetaLayerInfo::setFrom(const QJsonObject& json_object) {
    for (auto& key : json_object.keys()) {
        auto value = json_object.value(key).toString();;

        if (key == "description")
            description = value;
        else if (key == "url")
            json_file = value;
    }
}


//////////////////////////////////////////////////////////////////////////
// LayersInfo

LayersInfo::LayersInfo(QStringView json_file, ReadyCallback ready_callback):
    ready_callback_{ready_callback} {

    Downloader::instance().
        download<QJsonDocument>(WW_HOST_PATH(json_file.toString()),
            [this](auto result, auto&& json_doc) {
                if (result) {
                    getFromJson(json_doc);
                } else {
                    qDebug() << "Layers information loading failed";
                }
                ready_callback_(result);
            });
}

LayersInfo::~LayersInfo() = default;

void LayersInfo::clear() {
    meta_model_ = {};
    model_      = {};

    feature_layers_.clear();
}

void LayersInfo::getFromJson(const QJsonDocument json_doc) {
    auto json_object = json_doc.object();

    // Feature layers
    auto feature_layers = json_object["FeatureLayers"].toArray();

    for (auto&& layer : feature_layers) {
        auto layer_item = layer.toArray();

        if (layer_item.size() < 2) {
            qDebug() << "Invalid feature layer item";
            continue;
        }

        auto name       = layer_item[0].toString();
        auto properties = layer_item[1].toObject();

        feature_layers_.emplace_back(name, properties);
    }

    // Meta-model
    auto meta_model = json_object["Meta-Model"].toObject();
    meta_model_.setFrom(meta_model);

    // Model
    auto model = json_object["Model"].toObject();
    model_.setFrom(model);
}

} // namespace WaterwAIs
