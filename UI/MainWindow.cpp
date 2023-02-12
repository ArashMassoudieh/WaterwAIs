
#include "MainWindow.h"
#include "MapScene.h"
#include "MapView.h"

#include <Application/Defs.h>

#include <FeatureLayer/FeatureLayer.h>
#include <MetaModelLayer/MetaModelLayer.h>

#include <QVBoxLayout>
#include <QApplication>

#include <array>


namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MainWindow

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent), scene_(new MapScene(this)) {

    connect(this, &QObject::destroyed, this, [this](auto*) 
        { onBeforeAppDestroy(); });

    main_view_ = new MainView(this);
    mapView()->setScene(scene_);

    auto layout = new QVBoxLayout();
    layout->addWidget(main_view_);
    setLayout(layout);

    // Build layers.
    buildLayers();
}

void MainWindow::onBeforeAppDestroy() {
    main_view_->onBeforeAppDestroy();

    // Called just before the application is about to be destroyed,
    // so perform some cleanup here while the object is still alive.
}

void MainWindow::buildLayers() {
    // Show layers information downloading widget...
    msg_list_model_.setText(u"Downloading layer info...");
    main_view_->setMessageListModel(&msg_list_model_);    

    layers_info_ = std::make_unique<LayersInfo>(LAYERS_FILE,
        [this](auto result) { onLayersInfoLoaded(result); });
}

void MainWindow::onLayersInfoLoaded(bool result) {
    if (result) {
        // Hide layers downloading information.
        main_view_->setLayerListModel(&layers_list_model_);

#ifndef IGNORE_FEATURE_LAYERS
        // Add feature layers
        addFeatureLayers();
#endif // IGNORE_FEATURE_LAYERS

        // Add Meta model layer
        addMetaModelLayer();

        // Build the layer list model
        buildLayerListModel();
    } else {
        // Download failed.
        auto icon = QApplication::style()->standardIcon(QStyle::SP_BrowserStop);
        msg_list_model_.setText(u"Downloading layer info failed", icon);
    }
}


void MainWindow::addFeatureLayers() {
    // Building and adding layers
    auto& feature_layers = layers_info_->featureLayers();

    for (auto&& layer_info : feature_layers) {
        if (layer_info.json_file.isEmpty()) {
            qDebug() << "Layer: " << layer_info.name << " has empty JSON file";
            continue;
        }

        layers_.emplace_back(std::make_shared<FeatureLayer>
            (scene_, layer_info.name, layer_info.color, layer_info.json_file,
                layer_info.uses_shapes ? Layer::Option::UsesShapes
                : Layer::Option::None, layer_info.description));
    }
}

void MainWindow::addMetaModelLayer() {
    if (layers_info_->metaModel().json_file.isEmpty() ||
        layers_info_->model().json_file.isEmpty()) {
        qDebug() << "Meta-model/model has empty JSON file";
        return;
    }

    auto meta_model_layer = std::make_shared<MetaModelLayer>(scene_,
        u"Meta-Model",
        layers_info_->metaModel().json_file,
        layers_info_->model().json_file,
        layers_info_->model().description);

    layers_.emplace_back(meta_model_layer);
}

void MainWindow::buildLayerListModel() {
    // Adding layers to the layer list model
    for (auto&& layer : layers_) {
        connect(layer.get(), &Layer::layerReady,
            this, [this](auto) { zoomAll(); });

        // Adding layer to the layer list model.
        layers_list_model_.addLayer(layer);
    }
}

void MainWindow::zoomAll() {
    main_view_->mapView()->zoomToFit();
}

} // namespace WaterwAIs
