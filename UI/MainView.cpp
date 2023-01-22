
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>

#include <Layer/LayerListModel.h>
#include <Layer/LayerItemDelegate.h>

#include <Application/FileNameProcessor.h>

#include "MainView.h"
#include "MapView.h"
#include "ui_mainview.h"
#include "LayerPropertiesDialog.h"

#include <array>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MainView

MainView::MainView(QWidget* parent):
    QWidget(parent),
    ui(std::make_unique<Ui::MainView>()) {
    ui->setupUi(this);

    // Setting left part of the horizontal splitter to be 4 times less than
    // the right part.
    ui->splitter_2->setSizes(QList{100, 400});

    map_view_ = ui->mapView;
    ui->mapView->setMainView(this);

    // Setting up the layers list.
    setupLayerList();

    // Setting up tasks
    scheduleTasks();
}

MainView::~MainView() {}


void MainView::setStatusText(QStringView text) {
    ui->statusbar->setText(text.toString());
}


void MainView::setupLayerList() {
    ui->lstLayers->setItemDelegate(new LayerItemDelegate());
    submenu_.addAction("Properties");

    connect(&submenu_, &QMenu::triggered, this,
        [&](QAction* action) {
            if (action->text().contains("Properties")) {
                auto model = (LayerListModel*)ui->lstLayers->model();
                auto layer = (*model)[selected_item_].get();

                auto dlg = new LayerPropertiesDialog(layer, this);
                dlg->setModal(true);
                dlg->show();
            }
        });


    connect(ui->lstLayers, &QListView::customContextMenuRequested, this,
        [this](const QPoint& pos) {
            auto global_pos = ui->lstLayers->mapToGlobal(pos);

            auto idx = ui->lstLayers->indexAt(pos).row();
            if (idx < 0)
                return;

            selected_item_ = idx;
            submenu_.popup(global_pos);
        });
}


void MainView::scheduleTasks(std::chrono::milliseconds interval) {
    timer_.setInterval(interval);

    connect(&timer_, &QTimer::timeout, this, [this]() {
        auto req = QNetworkRequest{WW_SERVER_PATH("tasks/" + task_id_)};
        auto reply = network_mgr_.get(req);

        connect(reply, &QNetworkReply::finished, [this, reply]() {
            if (reply->error() == QNetworkReply::NetworkError::NoError) {
                auto err = QJsonParseError{};
                auto data = reply->readAll();
                auto doc = QJsonDocument::fromJson(data, &err);

                if (err.error != QJsonParseError::ParseError::NoError) {
                    qDebug() << "ERR, body: " << data;
                    timer_.stop();
                    return;
                }
                auto root_obj = doc.object();
                if (root_obj["task_status"] == "SUCCESS") {
                    timer_.stop();

                    auto fileId = root_obj["task_result"].toString();

                    qDebug() << "Finished, fileId: " << fileId;
                    getFile10LinesContent(fileId);
                } else {
                    qDebug() << "Still processing ...";
                }

                reply->deleteLater();
            } else {
                qDebug() << "Error occurred";
                timer_.stop();
            }
        });
    });
}


void MainView::setLayerListModel(QAbstractListModel* names) {
    ui->lstLayers->setModel(names);

    connect(ui->lstLayers->selectionModel(), &QItemSelectionModel::selectionChanged,
        this, [this](const QItemSelection& selected,
            const QItemSelection& /*deselected*/) {
        auto is_up   = true;
        auto is_down = true;

        if (selected.size() == 0) {
            is_up   = false;
            is_down = false;
        } else {
            int r = selected[0].indexes()[0].row();
            if (r == 0)
                is_up = false;            

            auto model = (LayerListModel*)ui->lstLayers->model();
            if (r == model->size() - 1)
                is_down = false;            
        }

        ui->btnMoveUp->setEnabled(is_up);
        ui->btnMoveDown->setEnabled(is_down);
    });
}

void MainView::setTableModel(MetaItemPropertyModel* propmodel) {
    qDebug() << ui->tableView->objectName();
    ui->tableView->setModel(propmodel);
}

void MainView::on_btnZoom_clicked() {
    map_view_->setMouseZoom();
    mapViewModesCheck();
}

void MainView::on_btnPan_clicked() {
    map_view_->setMousePan();
    mapViewModesCheck();
}

void MainView::on_btnFitToView_clicked() {
    map_view_->setFitToView();
    mapViewModesCheck();
}

void MainView::mapViewModesCheck() {
    auto mode = map_view_->mode();

    auto* checked_tool_btn = (QToolButton*)nullptr;

    switch (mode) {    
    case MapView::Mode::Pan:
        checked_tool_btn = ui->btnPan;
        break;
    case MapView::Mode::Zoom:
        checked_tool_btn = ui->btnZoom;
        break;
    case MapView::Mode::FitToView:
        checked_tool_btn = ui->btnFitToView;
        break;
    default:
        break;
    }

    auto buttons = std::array{ ui->btnPan, ui->btnZoom, ui->btnFitToView };

    for (auto button : buttons)
        button->setChecked(button == checked_tool_btn);

    if (!checked_tool_btn)
        map_view_->setNoneMode();
}


void MainView::on_btnMoveUp_clicked() {
    auto selected = ui->lstLayers->selectionModel()->selectedRows();
    if (selected.size() == 0)
        return;    

    auto row = selected[0].row();
    auto layers = (LayerListModel*)ui->lstLayers->model();
    if (row > 0)
        layers->moveLayer(row, row - 1);    
}

void MainView::on_btnMoveDown_clicked() {
    auto selected = ui->lstLayers->selectionModel()->selectedRows();
    if (selected.size() == 0)
        return;    

    auto row = selected[0].row();
    auto layers = (LayerListModel*)ui->lstLayers->model();

    if (row < layers->size() - 1)
        layers->moveLayer(row + 1, row);
}

void MainView::on_btnOpen_clicked() {
    auto fileContentReady = [this](const QString& fileName, const QByteArray& fileContent) {
        if (!fileName.isEmpty()) {
            if (!fileName.toLower().endsWith(".ohq")) {
                QMessageBox::critical(this, "Error", "Only accept ohq file extension!");
                return;
            }

            timer_.stop();

            auto req = QNetworkRequest{WW_SERVER_PATH(u"process")};
            req.setHeader(QNetworkRequest::ContentTypeHeader, QString("text/plain"));

            auto reply = network_mgr_.post(req, fileContent);

            connect(reply, &QNetworkReply::finished, this, [this, reply]() {
                if (reply->error() == QNetworkReply::NetworkError::NoError) {
                    auto data = reply->readAll();
                    task_id_ = data;
                    timer_.start();
                    reply->deleteLater();
                }
                });
        }
    };
    QFileDialog::getOpenFileContent("OHQ Files (*.ohq)", fileContentReady);
}

void MainView::getFile10LinesContent(QString fileId) {
    auto req = QNetworkRequest{WW_SERVER_PATH("file_10_lines/" + fileId)};
    auto reply = network_mgr_.get(req);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NetworkError::NoError) {
            qDebug() << "File content (first 10 lines):";
            qDebug() << reply->readAll();
            reply->deleteLater();
        }
        });
}

void MainView::getFileContent(QString fileId) {
    auto req = QNetworkRequest{WW_SERVER_PATH("files/" + fileId)};
    auto reply = network_mgr_.get(req);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NetworkError::NoError) {
            qDebug() << "File content:";
            qDebug() << reply->readAll();
            reply->deleteLater();
        }
    });
}

} // namespace WaterwAIs
