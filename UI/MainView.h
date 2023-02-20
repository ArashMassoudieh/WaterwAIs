
#ifndef MAINVIEW_H_9FF813C52C0F9D5D
#define MAINVIEW_H_9FF813C52C0F9D5D

#include <QWidget>
#include <QNetworkAccessManager>
#include <QMenu>
#include <QToolButton>
#include <QLabel>
#include <QTimer>

#include "MapView.h"

#include <MetaModelLayer/MetaItemPropertyModel.h>
#include <UI/Panel.h>

#include <chrono>

class QListView;
class QSortFilterProxyModel;
class QVBoxLayout;
class QHBoxLayout;

namespace Ui {
    class MainView;
}

namespace WaterwAIs {

using namespace std::chrono_literals;

class ChartInfo;
class LayerListModel;
class MessageListModel;
class MetaModelLayer;
class MetaLayerItem;
class GenericItemListModel;
class ItemNavigator;

//////////////////////////////////////////////////////////////////////////
// MainView

class MainView: public QWidget {
    friend class MainWindow;

    Q_OBJECT
public:
    using MetaModelLayerPtr = std::shared_ptr<MetaModelLayer>;
    using ItemNavigatorPtr  = std::shared_ptr<ItemNavigator>;

    explicit MainView(QWidget* parent = nullptr);
    ~MainView();

    MapView* mapView() { return map_view_; }

    // Layer list related functions
    void setMessageListModel(MessageListModel* msg_model = nullptr);
    void setLayerListModel(LayerListModel* names = nullptr);
        
    // Meta-model layer Item property table
    void setItemPropertiesModel(MetaItemPropertyModel* propmodel = nullptr,
        MetaLayerItem* layer_item = nullptr);

    // Navigate to layer item
    void navigateToLayerItem(const MetaLayerItem* layer_item);

    // Navigate to generic item
    void navigateToGenericItem(const QModelIndex& index);

    // Status text
    void setStatusText(QStringView text);

    // Displaying the chart in the lower panel.
    void showTimeSeries(QStringView item_name,  QStringView prop_name,
        QStringView ts_path, ItemNavigatorPtr item_navigator = {});


    void adjustMapViewControls(const QSize& adjustment);

protected slots:
    void onMetaModelLoaded(MetaModelLayerPtr model_layer);

    void on_btnZoom_clicked();
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnPan_clicked();
    void on_btnFitToView_clicked();

    void on_btnMoveUp_clicked();
    void on_btnMoveDown_clicked();
    void on_btnOpen_clicked();

    void on_btnTest_clicked();

private:
    using State = Panel::State;

    void createLayerListControls();
    void createMapViewControls();

    void onBeforeAppDestroy();
    void onModeButtonClicked(MapView::Mode mode);

    void zoomMapView(bool in);
    void mapViewModesCheck();

    // Layer list functions
    void setupLayerList();
    void setupPropertyPanel();
    void showLayerProperties();    
    
    // Generic items handling
    void setupGenItemPropertyPanel();
    void onGenericItemSelected(const QModelIndex& index = {});

    void scheduleTasks(std::chrono::milliseconds interval = 1s);

    void getFile10LinesContent(QString fileId);
    void getFileContent(QString fileId);

    bool spuriosButtonClick();

    std::unique_ptr<Ui::MainView> ui;

    MapView* map_view_;
    QMenu layers_submenu_;

    int selected_layer_idx_;

    QNetworkAccessManager network_mgr_;

    QString task_id_;
    QTimer timer_;    
     
    QToolButton* btnMoveUp_       = nullptr;
    QToolButton* btnMoveDown_     = nullptr;

    QToolButton* btn_pan_         = nullptr;
    QToolButton* btn_zoom_        = nullptr;
    QToolButton* btn_zoom_in_     = nullptr;
    QToolButton* btn_zoom_out_    = nullptr;
    QToolButton* btn_fit_to_view_ = nullptr;

    QHBoxLayout* button_layout_   = nullptr;

    QLabel*      status_bar_    = nullptr;
    QVBoxLayout* status_layout_ = nullptr;

    using Clock = std::chrono::steady_clock;
    Clock::time_point last_tb_clicked_ts_;

    std::unique_ptr<GenericItemListModel> gen_items_list_model_;    
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MAINVIEW_H_9FF813C52C0F9D5D
