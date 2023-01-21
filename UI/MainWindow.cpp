
#include "MainWindow.h"

#include "MapScene.h"

#include <FeatureLayer/FeatureLayer.h>
#include <MetaModelLayer/MetaModelLayer.h>
#include "MapView.h"

#include <QVBoxLayout>
#include <array>


namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// MainWindow

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent), scene_(new MapScene(this)) {

    main_view_ = new MainView(this);

    main_view_->setLayerListModel(&layers_list_model_);
    mapView()->setScene(scene_);

    auto layout = new QVBoxLayout();
    layout->addWidget(main_view_);
    setLayout(layout);

    // Build layers.
    buildLayers();
}

void MainWindow::buildLayers() {
    // Add feature layers
    addFeatureLayers();

    // Add Meta model layer
    addMetaModelLayer();

    // Build the layer list model
    buildLayerListModel();
}

void MainWindow::addFeatureLayers() {
    struct LayerInfo {
        QColor      color;
        QStringView json_file;
        bool        uses_shapes = true;
    };

    // Information about Feature layers.
    auto layer_infos = std::array {
        LayerInfo{Qt::red,    u"Centroids.geojson"},
        LayerInfo{Qt::blue,   u"HickeyRunSewer.geojson", false},
        LayerInfo{Qt::green,  u"PourPoints.geojson"},
        LayerInfo{Qt::yellow, u"SubWaterSheds.geojson"},
    };

    // Building and adding layers
   for (auto&& layer_info : layer_infos) {        
           layers_.emplace_back(std::make_shared<FeatureLayer>
               (scene_, layer_info.color, layer_info.json_file,
                   layer_info.uses_shapes ? Layer::Option::UsesShapes
                   : Layer::Option::None));
   }
}

void MainWindow::addMetaModelLayer() {
    auto component_json_file = u"meta_model.json";
    auto model_json_file     = u"Example_input.json";

    auto meta_model_layer = std::make_shared<MetaModelLayer>(scene_, 
        component_json_file, model_json_file);

    layers_.emplace_back(meta_model_layer);
}

void MainWindow::buildLayerListModel() {
    // Adding layers to the layer list model
    for (auto&& layer : layers_) {
        connect(layer.get(), &Layer::layerReady,
            this, [this]() { zoomAll(); });

        // Adding layer to the layer list model.
        layers_list_model_.addLayer(layer);
    }
}

void MainWindow::zoomAll() {
    main_view_->mapView()->zoomToFit();
}

} // namespace WaterWays
