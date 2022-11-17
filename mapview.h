#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QStringListModel>
#include <QNetworkAccessManager>
#include <QMenu>
#include <QTimer>

#include "graphicsview.h"
#include <QLabel>

namespace Ui {
class MapView;
}

class MapView : public QWidget
{
    Q_OBJECT

public:
    explicit MapView(QWidget *parent = nullptr);
    ~MapView();
    GraphicsView *view() { return MapViewer; }
    void setLayerListModel(QAbstractListModel *names);
    QLabel *StatusBar() {return statusbar;}

protected slots:
    void on_btnZoom_clicked();
    void on_btnPan_clicked();
    void on_btnFitToView_clicked();

    void on_btnMoveUp_clicked();
    void on_btnMoveDown_clicked();
    void on_btnOpen_clicked();

private:
    Ui::MapView *ui;
    GraphicsView* MapViewer;
    QMenu submenu;
    int selectedItem;
    QNetworkAccessManager nam;
    QString taskId;
    QTimer timer;

    void getFile10LinesContent(QString fileId);
    void getFileContent(QString fileId);
    QLabel *statusbar;
};

#endif // MAPVIEW_H
