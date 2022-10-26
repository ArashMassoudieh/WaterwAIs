#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QStringListModel>

#include "graphicsview.h"

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

protected slots:
    void on_btnZoom_clicked();
    void on_btnPan_clicked();
    void on_btnFitToView_clicked();

private:
    Ui::MapView *ui;
    GraphicsView* MapViewer;
};

#endif // MAPVIEW_H
