#include <climits>

#include <QDebug>
#include <QGraphicsItem>

#include "mapview.h"
#include "ui_mapview.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapView)
{
    ui->setupUi(this);
    MapViewer = ui->graphicsView;
}

MapView::~MapView()
{
    delete ui;
}

void MapView::on_btnZoom_clicked()
{
    MapViewer->setOperationType(GraphicsView::OperationType::Zoom);
}

void MapView::on_btnPan_clicked()
{
    MapViewer->setOperationType(GraphicsView::OperationType::Pan);
}

void MapView::on_btnFitToView_clicked()
{
    MapViewer->zoomToFit();
}
