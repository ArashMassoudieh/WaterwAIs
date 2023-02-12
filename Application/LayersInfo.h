
#ifndef LAYERSINFO_H_A419C6A9E72D1951
#define LAYERSINFO_H_A419C6A9E72D1951

#include <QString>
#include <QColor>
#include <vector>
#include <functional>

class QJsonDocument;
class QJsonObject;

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// FeatureLayerInfo

struct FeatureLayerInfo {
    FeatureLayerInfo(QStringView layer_name, const QJsonObject& json_object);

    QString name;
    QString description;
    QColor  color;
    QString json_file;
    bool    uses_shapes = true;
};


//////////////////////////////////////////////////////////////////////////
// MetaLayerInfo

struct MetaLayerInfo {
    QString description;
    QString json_file;

    void setFrom(const QJsonObject& json_object);
};


//////////////////////////////////////////////////////////////////////////
// LayersInfo

class LayersInfo {
public:
    // Called when Layers info is downloaded and parsed.
    // The download and parsing result is passed to notify about
    // success of the operations.
    using ReadyCallback = std::function<void(bool)>;

    LayersInfo(QStringView json_file, ReadyCallback ready_callback);
    ~LayersInfo();

    void clear();

    // Meta-Model
    const MetaLayerInfo& metaModel() const { return meta_model_; }

    // Model
    const MetaLayerInfo& model() const { return model_; }

    // Feature geo layers
    const std::vector<FeatureLayerInfo>& featureLayers() const
        { return feature_layers_; }

private:
    void getFromJson(const QJsonDocument json_doc);

    MetaLayerInfo meta_model_;
    MetaLayerInfo model_;

    std::vector<FeatureLayerInfo> feature_layers_;
    ReadyCallback ready_callback_;
};



} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // LAYERSINFO_H_A419C6A9E72D1951