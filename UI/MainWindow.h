
#ifndef MAINWINDOW_H_92E2E0638F6927FA
#define MAINWINDOW_H_92E2E0638F6927FA

#include <QWidget>

#include <Layer/Layer.h>
#include <Layer/LayerListModel.h>

#include "MainView.h"

namespace WaterwAIs {

class MapScene;
class MapView;
class MainView;
class MetaModelLayer;
class MetaLayerModel;

//////////////////////////////////////////////////////////////////////////
// MainWindow
//
// Main window of the application. Contains layers and layer list model.

class MainWindow: public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    
    // Map view, containing all layers
    MapView* mapView() { return main_view_->mapView(); }

protected:
    void onBeforeAppDestroy();

private:
    void buildLayers();

    void addFeatureLayers();
    void addMetaModelLayer();
    void buildLayerListModel();

    void zoomAll();

    MainView* main_view_;
    MapScene* scene_;

    // Feature Layers
    std::vector<Layer::Ptr> layers_;
    LayerListModel layers_list_model_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MAINWINDOW_H_92E2E0638F6927FA
