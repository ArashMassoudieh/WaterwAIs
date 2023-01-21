
#ifndef MAINVIEW_H_9FF813C52C0F9D5D
#define MAINVIEW_H_9FF813C52C0F9D5D

#include <QWidget>
#include <QStringListModel>
#include <QNetworkAccessManager>
#include <QMenu>
#include <QLabel>
#include <QTimer>
#include <QStandardItemModel>

#include <MetaModelLayer/MetaItemPropertyModel.h>

class QListView;

namespace Ui {
    class MainView;
}

namespace WaterWays {

class MapView;

//////////////////////////////////////////////////////////////////////////
// MainView

class MainView: public QWidget {
    Q_OBJECT

public:
    explicit MainView(QWidget* parent = nullptr);
    ~MainView();

    MapView* mapView() { return map_view_; }

    void setLayerListModel(QAbstractListModel* names);
    void setTableModel(MetaItemPropertyModel* propmodel);

    void setStatusText(QStringView text);

protected slots:
    void on_btnZoom_clicked();
    void on_btnPan_clicked();
    void on_btnFitToView_clicked();

    void on_btnMoveUp_clicked();
    void on_btnMoveDown_clicked();
    void on_btnOpen_clicked();

private:
    void mapViewModesCheck();

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
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // MAINVIEW_H_9FF813C52C0F9D5D
