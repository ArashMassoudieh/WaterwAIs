#include <climits>

#include <QDebug>
#include <QGraphicsItem>
#include <QMenu>
#include <QScreen>
#include <QFileDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>


#include "layeritemmodel.h"
#include "layeritemdelegate.h"
#include "mapview.h"
#include "ui_mapview.h"
#include "dlglayerproperties.h"

#include "Common.h"

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

    statusbar = new QLabel(this);
    ui->verticalLayout->addWidget(statusbar);
    MapViewer = ui->graphicsView;
    ui->graphicsView->SetMapView(this);

    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, [this]() {
        QNetworkRequest req(QString(SERVER_PATH) + "/tasks/" + taskId);
        auto reply = nam.get(req);
        connect(reply, &QNetworkReply::finished, [this, reply]() {
            if (reply->error() == QNetworkReply::NetworkError::NoError) {
                QJsonParseError err;
                auto data = reply->readAll();
                auto doc = QJsonDocument::fromJson(data, &err);
                if (err.error != QJsonParseError::ParseError::NoError) {
                    qDebug() << "ERR, body: " << data;
                    timer.stop();
                    return;
                }
                auto rootObj = doc.object();
                if (rootObj["task_status"] == "SUCCESS") {
                    timer.stop();

                    QString fileId = rootObj["task_result"].toString();

                    qDebug() << "Finished, fileId: " << fileId;
                    getFile10LinesContent(fileId);
                } else {
                    qDebug() << "Still processing ...";
                }

                reply->deleteLater();
            } else {
                qDebug() << "Error occured";
                timer.stop();
            }
        });
    });
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

void MapView::setTableModel(PropModel *propmodel)
{

    qDebug() << ui->tableView->objectName();
    ui->tableView->setModel(propmodel);
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

void MapView::on_btnOpen_clicked()
{
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
        if (fileName.isEmpty()) {
            // No file was selected
        } else {
            if (!fileName.toLower().endsWith(".ohq")) {
                QMessageBox::critical(this, "Error", "Only accept ohq file extension!");
                return;
            }

            timer.stop();
            QNetworkRequest req(QString(SERVER_PATH) + "/process");
            req.setHeader(QNetworkRequest::ContentTypeHeader, QString("text/plain"));
            auto reply = nam.post(req, fileContent);

            connect(reply, &QNetworkReply::finished, this, [this, reply]() {
                if (reply->error() == QNetworkReply::NetworkError::NoError) {
                    auto data = reply->readAll();
                    taskId = data;
                    timer.start();
                    reply->deleteLater();
                }
            });
        }
    };
    QFileDialog::getOpenFileContent("OHQ Files (*.ohq)",  fileContentReady);
}

void MapView::getFile10LinesContent(QString fileId)
{
    QNetworkRequest req(QString(SERVER_PATH) + "/file_10_lines/" + fileId);
    auto reply = nam.get(req);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NetworkError::NoError) {
            qDebug() << "File content (first 10 lines):";
            qDebug() << reply->readAll();
            reply->deleteLater();
        }
    });
}

void MapView::getFileContent(QString fileId)
{
    QNetworkRequest req(QString(SERVER_PATH) + "/files/" + fileId);
    auto reply = nam.get(req);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NetworkError::NoError) {
            qDebug() << "File content:";
            qDebug() << reply->readAll();
            reply->deleteLater();
        }
    });
}

QListView* MapView::LayersList()
{
    return ui->lstLayers;
}
