

#include "MainView.h"
#include "ui_mainview.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>

#include <Application/FileNameProcessor.h>

#include <Layer/LayerListModel.h>
#include <Layer/LayerItemDelegate.h>

#include <UI/MessageBox.h>

#include "MapView.h"
#include "LayerPropertiesDialog.h"
#include "ItemPropertiesWidget.h"
#include "Chart/ChartWidget.h"

#include <array>


namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MainView

MainView::MainView(QWidget* parent):
    QWidget(parent),
    ui(std::make_unique<Ui::MainView>()) {
    ui->setupUi(this);

    // Layer button icons
    auto up_icon = QApplication::style()->standardIcon(QStyle::SP_ArrowUp);
    ui->btnMoveUp->setIcon(up_icon);

    auto down_icon = QApplication::style()->standardIcon(QStyle::SP_ArrowDown);
    ui->btnMoveDown->setIcon(down_icon);

    auto open_icon = QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton);
    ui->btnOpen->setIcon(open_icon);


    // Creating Map view overlay controls
    createMapViewControls();

    ui->panelWidget->hide();

    // Setting left part of the horizontal splitter to be 4 times less than
    // the right part.
    ui->map_layers_splitter->setSizes(QList{100, 400});
    
    map_view_ = ui->mapView;
    ui->mapView->setMainView(this);

    // Setting up the layers list.
    setupLayerList();

    // Setting up the item property panel
    setupPropertyPanel();

    // Setting up tasks
    scheduleTasks();

    // Setting panel widget to be twice less than the map view.
    ui->panel_splitter->setSizes(QList{200, 100});
}

MainView::~MainView() {}


void MainView::createMapViewControls() {
    // Tool buttons
    button_layout_ = new QHBoxLayout{};
    button_layout_->setSpacing(1);
    
    auto icon_size = QSize{24,24};

    auto add_tool_button = [&](QStringView name, QStringView icon_file,
        QStringView text = {}, QStringView tooltip = {}, bool checkable = false) {

        auto button = new QToolButton{};
        button->setObjectName(name.toString());

        button->setText(text.toString());
        button->setIcon(QIcon{icon_file.toString()});
        button->setToolTip(tooltip.toString());
        button->setCheckable(checkable);

        if (!text.isEmpty())
            button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        button->setIconSize(icon_size);
        button_layout_->addWidget(button);

        return button;
    };
    
    // Pan
    btn_pan_ = add_tool_button(u"btnPan", u":/Resources/hand-rock.png", u"Pan",
        u"Panning the view by mouse", true);

    // Zoom
    btn_zoom_ = add_tool_button(u"btnZoom", u":/Resources/zoom.png", u"Zoom",
        u"Zooming the view by mouse", true);

    // Zoom in
    btn_zoom_in_ = add_tool_button(u"btnZoomIn", u":/Resources/zoomin.png", {},
        u"Zooming in the view");
    
    // Zoom Out
    btn_zoom_out_ = add_tool_button(u"btnZoomOut", u":/Resources/zoomout.png", {},
        u"Zooming out the view");

    // Fit in View
    btn_fit_to_view_ = add_tool_button(u"btnFitToView", u":/Resources/expand.png", 
        u"Fit View", u"Fit in view", true);
    
    ui->gridLayout->addLayout(button_layout_, 0, 0,
        Qt::AlignRight | Qt::AlignTop);

    // Status bar for coordinates
    status_bar_ = new QLabel();

    status_layout_ = new QVBoxLayout{};
    status_layout_->addWidget(status_bar_);

    ui->gridLayout->addLayout(status_layout_, 0, 0,
            Qt::AlignLeft | Qt::AlignBottom);
    
    QMetaObject::connectSlotsByName(this);
}


void MainView::adjustMapViewControls(const QSize& adjustment) {
    // Adjusting the Map view overlay controls based on reported difference
    // between the Map view and its viewport. 
    // This will move controls into correct positions in the map view without
    // overlapping with the view scrollbars.
    button_layout_->setContentsMargins(0, 0, adjustment.width(), 0);
    status_layout_->setContentsMargins(0, 0, 0, adjustment.height());
}


void MainView::onBeforeAppDestroy() {
    map_view_->onBeforeAppDestroy();

    // Called just before the application is about to be destroyed,
    // so perform some cleanup here while the object is still alive.
}


void MainView::setStatusText(QStringView text) {
    status_bar_->setText(text.toString());
}

void MainView::setupPropertyPanel() {
    auto property_widget = new ItemPropertiesWidget{this};

    connect(property_widget, &ItemPropertiesWidget::showTimeSeries, this,
        [this](auto item, auto name, auto ts_path) { 
            showTimeSeries(item, name, ts_path);
        });

    ui->propertyPanel->setWidget(property_widget);

    ui->propertyPanel->setTitleText(u"Item:");

    // We don't close property panel.
    ui->propertyPanel->setCloseable(false);    
}

void MainView::setupLayerList() {
    ui->lstLayers->setItemDelegate(new LayerItemDelegate());
    submenu_.addAction("Properties");

    connect(&submenu_, &QMenu::triggered, this,
        [&](QAction* action) {
            if (action->text().contains("Properties"))
                showLayerProperties();            
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

    connect(ui->lstLayers, &QListView::doubleClicked, this,
        [this](const auto& index) {
            selected_item_ = index.row();
            showLayerProperties();
        });
}

void MainView::showLayerProperties() {
    auto model = (LayerListModel*)ui->lstLayers->model();
    auto layer = (*model)[selected_item_].get();

    auto dlg = new LayerPropertiesDialog(layer, this);
    dlg->setModal(true);
    dlg->show();
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
            auto r = static_cast<size_t>(selected[0].indexes()[0].row());
            if (r == 0)
                is_up = false;            

            auto model = static_cast<LayerListModel*>(ui->lstLayers->model());
            if (r == model->size() - 1)
                is_down = false;            
        }

        ui->btnMoveUp  ->setEnabled(is_up);
        ui->btnMoveDown->setEnabled(is_down);
    });
}

void MainView::setTableModel(MetaItemPropertyModel* propmodel) {
    auto property_widget = 
        qobject_cast<ItemPropertiesWidget*>(ui->propertyPanel->getWidget());

    Q_ASSERT(property_widget);

    property_widget->setTableModel(propmodel);
}

void MainView::on_btnZoom_clicked() {
    map_view_->setMouseZoom();
    mapViewModesCheck();
}

void MainView::zoomMapView(bool in) {
    if (map_view_->mode() == MapView::Mode::FitToView)
        on_btnPan_clicked();

    map_view_->zoom(in);
}

void MainView::on_btnZoomIn_clicked()  {
    zoomMapView(true);
}

void MainView::on_btnZoomOut_clicked() {
    zoomMapView(false);
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
        checked_tool_btn = btn_pan_;
        break;
    case MapView::Mode::Zoom:
        checked_tool_btn = btn_zoom_;
        break;
    case MapView::Mode::FitToView:
        checked_tool_btn = btn_fit_to_view_;
        break;
    default:
        break;
    }

    auto buttons = std::array{btn_pan_, btn_zoom_, btn_fit_to_view_};

    for (auto button : buttons)
        button->setChecked(button == checked_tool_btn);

    if (!checked_tool_btn)
        map_view_->setNoneMode();
}


void MainView::on_btnMoveUp_clicked() {
    if (spuriosButtonClick())
        return;

    auto selected = ui->lstLayers->selectionModel()->selectedRows();
    if (selected.size() == 0)
        return;    

    auto row = selected[0].row();
    auto layers = static_cast<LayerListModel*>(ui->lstLayers->model());

    if (row > 0) {
        if (layers->moveLayer(row, row - 1)) {
            auto index = ui->lstLayers->model()->index(row - 1, 0);
            ui->lstLayers->setCurrentIndex(index);
        } else {
            MessageBox::information("Layers", "This layer cannot be moved up");
        }
    }
}

bool MainView::spuriosButtonClick() {
    if (last_tb_clicked_ts_ == Clock::time_point{}) {
        // First click
        last_tb_clicked_ts_ = Clock::now();
        return false;
    }
    
    if (Clock::now() - last_tb_clicked_ts_ < 100ms) {
        // Spurious second click
        last_tb_clicked_ts_ = Clock::time_point{};
        return true;
    }
    return false;
}

void MainView::on_btnMoveDown_clicked() {
    if (spuriosButtonClick())
        return;

    auto selected = ui->lstLayers->selectionModel()->selectedRows();
    if (selected.size() == 0)
        return;

    auto row = static_cast<size_t>(selected[0].row());
    auto layers = static_cast<LayerListModel*>(ui->lstLayers->model());

    if (row < layers->size() - 1) {
        if (layers->moveLayer(row + 1, row)) {
            auto index = ui->lstLayers->model()->index(row +1, 0);
            ui->lstLayers->setCurrentIndex(index);
        } else {
            MessageBox::information("Layers", "This layer cannot be moved up");
        }
    }
}

void MainView::on_btnOpen_clicked() {
    if (spuriosButtonClick())
        return;

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

void MainView::showTimeSeries(QStringView item_name, QStringView prop_name,
    QStringView ts_path) {
    auto chart_info = ChartInfo{prop_name, ts_path};

    auto panel_widget = 
        qobject_cast<ChartWidget*>(ui->panelWidget->getWidget());

    if (!panel_widget || panel_widget->chartInfo() != chart_info) {
        auto chart_widget = new ChartWidget{chart_info};

        ui->panelWidget->setWidget(chart_widget);
        ui->panelWidget->setIcon(u":/Resources/chart.png");

        ui->panelWidget->setTitleText(item_name.toString() + " - " +
            chart_info.name());
    }    
    ui->panelWidget->show();
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
