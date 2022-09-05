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
