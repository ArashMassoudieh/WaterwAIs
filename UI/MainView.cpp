

#include "MainView.h"
#include "ui_mainview.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>

#include <Application/FileNameProcessor.h>

#include <Layer/LayerListModel.h>
#include <Layer/LayerItemDelegate.h>

#include <MetaModelLayer/MetaModelLayer.h>
#include <MetaModelLayer/MetaLayerModel.h>
#include <MetaModelLayer/NodeLayerItem.h>
#include <MetaModelLayer/GenericItemListModel.h>

#include <UI/MessageBox.h>

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

    // Creating Map view overlay controls
    createMapViewControls();

    ui->panelWidget->hide();

    // Setting left part of the horizontal splitter to be 4 times less than
    // the right part.
    ui->map_layers_splitter->setSizes(QList{100, 400});
    
    map_view_ = ui->mapView;
    ui->mapView->setMainView(this);    

    // Setting up the item property panel
    setupPropertyPanel();

    // Setting up the 'generic' item property panel
    setupGenItemPropertyPanel();

    // Setting up tasks
    scheduleTasks();

    // Setting panel widget to be twice less than the map view.
    ui->panel_splitter->setSizes(QList{200, 100});

    QMetaObject::connectSlotsByName(this);
}

MainView::~MainView() {}

void MainView::createLayerListControls() {
    // Tool buttons
    auto button_layout = new QHBoxLayout{};
    button_layout->setSpacing(1);
    
    // Move Up
    btnMoveUp_ = new QToolButton{};
    btnMoveUp_->setObjectName("btnMoveUp");

    auto icon = QApplication::style()->standardIcon(QStyle::SP_ArrowUp);
    btnMoveUp_->setIcon(icon);
    btnMoveUp_->setToolTip("Moves layer up");
    button_layout->addWidget(btnMoveUp_);

    // Move Down
    btnMoveDown_ = new QToolButton{};
    btnMoveDown_->setObjectName("btnMoveDown");

    icon = QApplication::style()->standardIcon(QStyle::SP_ArrowDown);
    btnMoveDown_->setIcon(icon);
    btnMoveDown_->setToolTip("Moves layer down");
    button_layout->addWidget(btnMoveDown_);

    ui->gridLayout_layers->addLayout(button_layout, 0, 0,
        Qt::AlignRight | Qt::AlignTop);

    QMetaObject::connectSlotsByName(this);
}


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
    btn_pan_ = add_tool_button(u"btnPan", u":/Resources/hand-rock.png", {}, //u"Pan",
        u"Panning the view by mouse", true);

    // Zoom
    btn_zoom_ = add_tool_button(u"btnZoom", u":/Resources/zoom.png", {}, //u"Zoom",
        u"Zooming the view by mouse", true);

    // Zoom in
    btn_zoom_in_ = add_tool_button(u"btnZoomIn", u":/Resources/zoomin.png", {},
        u"Zooming in the view");
    
    // Zoom Out
    btn_zoom_out_ = add_tool_button(u"btnZoomOut", u":/Resources/zoomout.png", {},
        u"Zooming out the view");

    // Fit in View
    btn_fit_to_view_ = add_tool_button(u"btnFitToView", u":/Resources/expand.png", 
        {}, u"Fit in view", true);
    
    // Test button
    //add_tool_button(u"btnTest", {}, u"Test button");

    ui->gridLayout->addLayout(button_layout_, 0, 0,
        Qt::AlignRight | Qt::AlignTop);

    // Status bar for coordinates
    status_bar_ = new QLabel();

    status_layout_ = new QVBoxLayout{};
    status_layout_->addWidget(status_bar_);

    ui->gridLayout->addLayout(status_layout_, 0, 0,
            Qt::AlignLeft | Qt::AlignBottom);    
}

void MainView::on_btnTest_clicked() {
    // test code..
}

void MainView::onMetaModelLoaded(MetaModelLayerPtr model_layer) {
    gen_items_list_model_.reset();
    auto model = model_layer->to_model<MetaLayerModel>();

    if (!model->genericItemMap().empty()) {
        // We have some generic items, so let's shoe the panel for them.
        ui->gen_panel_splitter->show();

        //Fill the generic item list widget...
        gen_items_list_model_ = 
            std::make_unique<GenericItemListModel>(*model, this);        

        ui->genericItemsList->setIconSize(QSize(24, 24));
        ui->genericItemsList->setModel(gen_items_list_model_.get());

        auto selection_model = ui->genericItemsList->selectionModel();

        connect(selection_model, &QItemSelectionModel::selectionChanged, this,
            [this](const auto& selected, const auto&) {
                auto indexes = selected.indexes();

                if (!indexes.isEmpty()) {
                    auto& index = indexes.front();
                    onGenericItemSelected(index);
                } else {
                    onGenericItemSelected();
                }
            });

        ui->map_layers_splitter->setSizes(QList{100, 400, 100});
    }
}

//////////////////////////////////////////////////////////////////////////
// GenericItemNavigator
class GenericItemNavigator: public ItemNavigator {
public:
    using GenericItem = MetaLayerModelItems::GenericItem;

    GenericItemNavigator(const QModelIndex& index, 
        const GenericItem* generic_item, MainView* main_view):
        index_{index}, generic_item_{generic_item}, main_view_{main_view} {}

    // Returns item's icon
    QIcon itemIcon() const override { 
        return generic_item_->component().icon();
    }

    // Performs navigating to the item
    void navigate() override
        { main_view_->navigateToGenericItem(index_); }
private:
    QModelIndex index_;
    const GenericItem* generic_item_;    
    MainView* main_view_;
};


void MainView::onGenericItemSelected(const QModelIndex& index) {
    auto property_widget =
        qobject_cast<ItemPropertiesWidget*>(ui->propertyGenPanel->getWidget());

    Q_ASSERT(property_widget);

    if (!index.isValid()) {
        property_widget->setTableModel(nullptr);
        return;
    }

    auto generic_item = gen_items_list_model_->getItem(index);
    Q_ASSERT(generic_item);
    
    // Set property model
    auto prop_model = 
        std::make_unique<MetaItemPropertyModel>(*generic_item, this);

    property_widget->setTableModel(prop_model.release());

    // Set navigator
    property_widget->setNavigator(std::make_shared<GenericItemNavigator>
        (index, generic_item, this));
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
        [this](auto item, auto name, auto ts_path, auto item_navigator) { 
            showTimeSeries(item, name, ts_path, item_navigator);
        });

    ui->propertyPanel->setWidget(property_widget);

    ui->propertyPanel->setTitleText(u"Item:");

    // We don't close property panel.
    ui->propertyPanel->setCloseable(false);
}

void MainView::setupGenItemPropertyPanel() {   
    gen_items_list_model_.reset();
    ui->gen_panel_splitter->hide();

    auto property_widget = new ItemPropertiesWidget{this};

     connect(property_widget, &ItemPropertiesWidget::showTimeSeries, this,
         [this](auto item, auto name, auto ts_path, auto item_navigator) {
             showTimeSeries(item, name, ts_path, item_navigator);
         });

    ui->propertyGenPanel->setWidget(property_widget);
    ui->propertyGenPanel->setTitleText(u"Item:");

    // We don't close property panel.
    ui->propertyGenPanel->setCloseable(false);
}


void MainView::setupLayerList() {
    // Creating Layer list controls
    createLayerListControls();

    ui->lstLayers->setItemDelegate(new LayerItemDelegate());
    layers_submenu_.addAction("Properties");

    connect(&layers_submenu_, &QMenu::triggered, this,
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

            selected_layer_idx_ = idx;
            layers_submenu_.popup(global_pos);
        });

    connect(ui->lstLayers, &QListView::doubleClicked, this,
        [this](const auto& index) {
            selected_layer_idx_ = index.row();
            showLayerProperties();
        });
}

void MainView::showLayerProperties() {
    auto model = (LayerListModel*)ui->lstLayers->model();
    auto layer = (*model)[selected_layer_idx_].get();

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

void MainView::setMessageListModel(MessageListModel* msg_model) {
    ui->lstLayers->setModel(msg_model);
}


void MainView::setLayerListModel(LayerListModel* names) {    
    setupLayerList();

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

        btnMoveUp_  ->setEnabled(is_up);
        btnMoveDown_->setEnabled(is_down);
    });

    connect(names, &LayerListModel::layerMoved, this, [this](int to) {
        // Updating selected layer after moving.
        auto index = ui->lstLayers->model()->index(to, 0);
        ui->lstLayers->setCurrentIndex(index);        
    });
}

//////////////////////////////////////////////////////////////////////////
// LayerItemNavigator

class LayerItemNavigator: public ItemNavigator {
public:
    LayerItemNavigator(MetaLayerItem* layer_item, MainView* main_view):
        layer_item_{layer_item}, main_view_{main_view}{}
    
    // Returns item's icon
    QIcon itemIcon() const override
        { return layer_item_->modelItem().component().icon(); }

    // Performs navigating to the item
    void navigate() override
        { main_view_->navigateToLayerItem(layer_item_); }

private:
    MetaLayerItem* layer_item_;
    MainView* main_view_;
};


void MainView::setItemPropertiesModel(MetaItemPropertyModel* propmodel, 
    MetaLayerItem* layer_item) {
    auto property_widget = 
        qobject_cast<ItemPropertiesWidget*>(ui->propertyPanel->getWidget());

    Q_ASSERT(property_widget);
    
    if (layer_item) {
        property_widget->setNavigator
            (std::make_shared<LayerItemNavigator>(layer_item, this));
    } else
        property_widget->setNavigator();    

    property_widget->setTableModel(propmodel);
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

void MainView::on_btnZoom_clicked() {
    onModeButtonClicked(MapView::Mode::Zoom);
}

void MainView::on_btnPan_clicked() {
    onModeButtonClicked(MapView::Mode::Pan);
}

void MainView::on_btnFitToView_clicked() {
    onModeButtonClicked(MapView::Mode::FitToView);

    // Apply set fit view immediately after we changed the mode. 
    if (map_view_->mode() == MapView::Mode::FitToView)
        map_view_->setFitToView();
}

void MainView::onModeButtonClicked(MapView::Mode mode) {
    if (spuriosButtonClick())
        return;

    auto view_mode = map_view_->mode();

    if (view_mode != mode)
        map_view_->setMode(mode);
    else
        map_view_->setNoneMode();

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
    
    if (Clock::now() - last_tb_clicked_ts_ < 200ms) {
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

    auto row = selected[0].row();
    auto layers = static_cast<LayerListModel*>(ui->lstLayers->model());

    if (row < static_cast<int>(layers->size()) - 1) {        
        if (!layers->moveLayer(row, row + 1))
            MessageBox::information("Layers", "This layer cannot be moved down");
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
    QStringView ts_path, ItemNavigatorPtr item_navigator) {
    auto chart_info = ChartInfo{prop_name, ts_path};

    auto panel_widget = 
        qobject_cast<ChartWidget*>(ui->panelWidget->getWidget());

    if (!panel_widget || panel_widget->chartInfo() != chart_info) {
        auto chart_widget = new ChartWidget{chart_info};
        chart_widget->setNavigator(item_navigator);

        ui->panelWidget->setWidget(chart_widget);
        ui->panelWidget->setIcon(u":/Resources/chart.png");

        ui->panelWidget->setTitleText(item_name.toString() + " - " +
            chart_info.name());
    }    
    ui->panelWidget->show();
}

void MainView::navigateToLayerItem(const MetaLayerItem* layer_item) {
    if (layer_item)
        ui->mapView->centerOn(layer_item);
}

void MainView::navigateToGenericItem(const QModelIndex& index) {
    if (index.isValid())
        ui->genericItemsList->scrollTo(index);
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
