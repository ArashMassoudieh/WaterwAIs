#include <climits>

#include <QDebug>
#include <QGraphicsItem>
#include <QMenu>
#include <QScreen>

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

    submenu.addAction("Properties");
    connect(&submenu, &QMenu::triggered, this, [&](QAction* action) {
        if (action->text().contains("Properties")) {
            auto model = (LayerItemModel *) ui->lstLayers->model();
            auto layer = (*model)[selectedItem].get();

            auto dlg = new DlgLayerProperties(layer, this);
            dlg->setModal(true);
            dlg->show();
        }
    });


    connect(ui->lstLayers, &QListView::customContextMenuRequested, this, [this](const QPoint &pos) {
        QPoint gloPos = ui->lstLayers->mapToGlobal(pos);
        auto idx = ui->lstLayers->indexAt(pos).row();
        if (idx < 0) {
            return;
        }

        selectedItem = idx;
        submenu.popup(gloPos);
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

    connect(ui->lstLayers->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this](const QItemSelection &selected, const QItemSelection &deselected) {
        bool isUp = true;
        bool isDown = true;

        if (selected.size() == 0) {
            isUp = false;
            isDown = false;
        } else {
            int r = selected[0].indexes()[0].row();
            if (r == 0) {
                isUp = false;
            }

            auto model = (LayerItemModel *) ui->lstLayers->model();
            if (r == model->getCount() - 1) {
                isDown = false;
            }
        }

        ui->btnMoveUp->setEnabled(isUp);
        ui->btnMoveDown->setEnabled(isDown);
    });
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

void MapView::on_btnMoveUp_clicked()
{
    auto selected = ui->lstLayers->selectionModel()->selectedRows();
    if (selected.size() == 0) {
        return;
    }

    auto r = selected[0].row();
    auto layers = (LayerItemModel *) ui->lstLayers->model();
    if (r > 0) {
        layers->moveItem(r, r-1);
    }
}

void MapView::on_btnMoveDown_clicked()
{
    auto selected = ui->lstLayers->selectionModel()->selectedRows();
    if (selected.size() == 0) {
        return;
    }

    auto r = selected[0].row();
    auto layers = (LayerItemModel *) ui->lstLayers->model();
    if (r < layers->getCount() - 1) {
        layers->moveItem(r+1, r);
    }
}
