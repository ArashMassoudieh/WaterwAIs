#include <climits>

#include <QDebug>
#include <QGraphicsItem>
#include <QMenu>

#include "layeritemmodel.h"
#include "layeritemdelegate.h"
#include "mapview.h"
#include "ui_mapview.h"
#include "dlglayerproperties.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapView)
{
    ui->setupUi(this);
    ui->lstLayers->setItemDelegate(new LayerItemDelegate());
    ui->lstLayers->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->lstLayers->setDragEnabled(true);
    ui->lstLayers->setAcceptDrops(true);
    ui->lstLayers->setDropIndicatorShown(true);

    connect(ui->lstLayers, &QListView::customContextMenuRequested, this, [this](const QPoint &pos) {
        QPoint item = ui->lstLayers->mapToGlobal(pos);
        auto idx = ui->lstLayers->indexAt(pos).row();
        auto model = (LayerItemModel *) ui->lstLayers->model();
        auto layer = (*model)[idx].get();

        QMenu submenu;
        submenu.addAction("Properties");
        QAction* action = submenu.exec(item);
        if (action && action->text().contains("Properties")) {
            auto dlg = new DlgLayerProperties(layer, this);
            dlg->setModal(true);
            dlg->show();
        }
    });

    MapViewer = ui->graphicsView;
}

MapView::~MapView()
{
    delete ui;
}

void MapView::setLayerListModel(QAbstractListModel *names)
{
    ui->lstLayers->setModel(names);
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
