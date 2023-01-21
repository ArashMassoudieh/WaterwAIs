
#ifndef FEATURELAYER_H_A84962A48953B829
#define FEATURELAYER_H_A84962A48953B829

#include <Layer/Layer.h>
#include <Layer/LayerModel.h>
#include "FeatureModelItem.h"

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// FeatureLayerModel

class FeatureLayerModel : public LayerModel {
    Q_OBJECT
public:    

    // Returns the layer feature type set during model loading from JSON.
    FeatureType getFeatureType() { return feature_type_; }

protected:
    // Fills the model from some JSON document    
    void getFromJsonDocument(const QJsonDocument& json_doc) override;

private:
    using FeaturePtr = FeatureModelItem::Ptr;

    FeatureType feature_type_;
    std::vector<FeaturePtr> features_;
};

//////////////////////////////////////////////////////////////////////////
// FeatureLayer

class FeatureLayer: public Layer {
public:
    FeatureLayer(LayerSceneInterface* scene, const QColor& color = Qt::black,
        QStringView json_file = {}, Options options = Option::None);

    FeatureType getFeatureType() { 
        auto model = to_model<FeatureLayerModel>();
        return model ? model->getFeatureType() : FeatureType::Unknown;
    }
private:      
};


} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // FEATURELAYER_H_A84962A48953B829