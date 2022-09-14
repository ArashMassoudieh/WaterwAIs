#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
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
    GraphicsView *view() {return MapViewer;}

protected slots:
    void on_btnFitToView_clicked();

private:
    Ui::MapView *ui;
    GraphicsView* MapViewer;
};

#endif // MAPVIEW_H
