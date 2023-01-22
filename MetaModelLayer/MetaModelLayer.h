#ifndef METAMODELLAYER_H_8DD8274EB9E21362
#define METAMODELLAYER_H_8DD8274EB9E21362

#include <Layer/Layer.h>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MetaModelLayer

class MetaModelLayer: public Layer {
public:
    MetaModelLayer(LayerSceneInterface* scene,
        QStringView component_json_file = {}, QStringView json_file = {});

private:
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // METAMODELLAYER_H_8DD8274EB9E21362
