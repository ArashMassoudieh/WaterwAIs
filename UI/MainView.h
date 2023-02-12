
#ifndef MAINVIEW_H_9FF813C52C0F9D5D
#define MAINVIEW_H_9FF813C52C0F9D5D

#include <QWidget>
#include <QStringListModel>
#include <QNetworkAccessManager>
#include <QMenu>
#include <QToolButton>
#include <QLabel>
#include <QTimer>
#include <QStandardItemModel>

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

class MapView;
class ChartInfo;
class LayerListModel;
class MessageListModel;

//////////////////////////////////////////////////////////////////////////
// MainView

class MainView: public QWidget {
    friend class MainWindow;

    Q_OBJECT
public:
    explicit MainView(QWidget* parent = nullptr);
    ~MainView();

    MapView* mapView() { return map_view_; }

    void setMessageListModel(MessageListModel* msg_model = nullptr);
    void setLayerListModel(LayerListModel* names = nullptr);


    void setTableModel(MetaItemPropertyModel* propmodel = nullptr);

    void setStatusText(QStringView text);

    void adjustMapViewControls(const QSize& adjustment);

    // Displaying the chart in the lower panel.
    void showTimeSeries(QStringView item_name,  QStringView prop_name,
        QStringView ts_path);

protected slots:
    void on_btnZoom_clicked();
    void on_btnZoomIn_clicked();
    void on_btnZoomOut_clicked();
    void on_btnPan_clicked();
    void on_btnFitToView_clicked();

    void on_btnMoveUp_clicked();
    void on_btnMoveDown_clicked();
    void on_btnOpen_clicked();

private:
    using State = Panel::State;

    void createLayerListControls();
    void createMapViewControls();

    void onBeforeAppDestroy();

    void zoomMapView(bool in);
    void mapViewModesCheck();

    void showLayerProperties();

    void setupLayerList();
    void setupPropertyPanel();

    void scheduleTasks(std::chrono::milliseconds interval = 1s);

    void getFile10LinesContent(QString fileId);
    void getFileContent(QString fileId);

    bool spuriosButtonClick();

    std::unique_ptr<Ui::MainView> ui;

    MapView* map_view_;
    QMenu submenu_;

    int selected_item_;

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
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MAINVIEW_H_9FF813C52C0F9D5D
