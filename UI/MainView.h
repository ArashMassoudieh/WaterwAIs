
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

class QListView;

namespace Ui {
    class MainView;
}

namespace WaterwAIs {

class MapView;

//////////////////////////////////////////////////////////////////////////
// MainView

class MainView: public QWidget {
    friend class MainWindow;

    Q_OBJECT
public:
    explicit MainView(QWidget* parent = nullptr);
    ~MainView();

    MapView* mapView() { return map_view_; }

    void setLayerListModel(QAbstractListModel* names = nullptr);
    void setTableModel(MetaItemPropertyModel* propmodel = nullptr);

    void setStatusText(QStringView text);

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
    void createMapViewControls();
    void onBeforeAppDestroy();

    void zoomMapView(bool in);
    void mapViewModesCheck();

    void showLayerProperties();

    void setupLayerList();
    void scheduleTasks(std::chrono::milliseconds interval = 1s);

    void getFile10LinesContent(QString fileId);
    void getFileContent(QString fileId);

    std::unique_ptr<Ui::MainView> ui;

    MapView* map_view_;
    QMenu submenu_;

    int selected_item_;

    QNetworkAccessManager network_mgr_;

    QString task_id_;
    QTimer timer_;

    MetaItemPropertyModel* properties_model_;
     
    QToolButton* btn_pan_         = nullptr;
    QToolButton* btn_zoom_        = nullptr;
    QToolButton* btn_zoom_in_     = nullptr;
    QToolButton* btn_zoom_out_    = nullptr;
    QToolButton* btn_fit_to_view_ = nullptr;

    QLabel* status_bar_ = nullptr;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MAINVIEW_H_9FF813C52C0F9D5D
