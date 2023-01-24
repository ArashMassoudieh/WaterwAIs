
#include "MapView.h"
#include "MapScene.h"
#include "MainWindow.h"

#include <MetaModelLayer/MetaModelLayer.h>
#include <MetaModelLayer/MetaLayerModel.h>

#include <MetaModelLayer/NodeLayerItem.h>
#include <MetaModelLayer/LinkLayerItem.h>

#include <QListView>
#include <QDebug>
#include <QMouseEvent>
#include <QPen>
#include <QColor>


namespace WaterwAIs {

namespace {
    auto constexpr zoom_color = QColor(100, 100, 100);
    auto constexpr zoom_rect_zvalue = 50000;
} // anonymous

//////////////////////////////////////////////////////////////////////////
// MapView

MapView::MapView(QWidget* parent)
    : QGraphicsView{parent} {
    mode_ = Mode::None;
    zoom_rect_ = nullptr;
}

MapView::~MapView() {
}


void MapView::onBeforeAppDestroy() {
    // Clearing the selected items before destruction while we still have
    // objects alive.
    clearSelection();
}

void MapView::zoomToFit() {
    fitInView(mapScene()->boundingRect(), Qt::KeepAspectRatio);
    repaint();
}

void MapView::setFitToView() {
    setMode(Mode::FitToView);
    
    // Setting not-panned scene rectangle
    setSceneRect(mapScene()->boundingRect());
    zoomToFit();
}

void MapView::onModeSet() {
    // Clear things from the previous modes.
    zoom_rect_           = nullptr;
    last_point_          = {};
    last_scene_rect_     = {};
    pressed_scene_point_ = {};
}

void MapView::clearSelection(bool on_destroy) {
    // Clear selected items
    if (on_destroy) {
        // Clearing the selected items during destruction if there are any,
        //  as they may be stale and already destroyed.
        for (auto& sel_item : selected_items_)
            sel_item.clear();

        return;
    }

    selected_items_.clear();

    // Clear the properties table
    main_view_->setTableModel();
}


void MapView::mousePressEvent(QMouseEvent* event) {
    if (event->button() & Qt::LeftButton) {
        is_pressed_ = true;
        last_point_ = event->pos();
        pressed_scene_point_ = mapToScene(event->pos());
        
        selectItem(last_point_);
    } else {
        QGraphicsView::mousePressEvent(event);
        return;
    }

    auto map_scene = mapScene();

    switch (mode_) {
    case Mode::Pan:
        setCursor(Qt::ClosedHandCursor);
        break;

    case Mode::Zoom: {
        auto scene_rc = map_scene->sceneRect();

        auto zoom_ratio_width  = scene_rc.width()  / map_scene->boundingRect().width();
        auto zoom_ratio_height = scene_rc.height() / map_scene->boundingRect().height();
        auto zoom_ratio = std::min(zoom_ratio_width, zoom_ratio_height);

        Q_ASSERT(zoom_rect_ == nullptr);

        zoom_rect_ = map_scene->addRect(QRectF{pressed_scene_point_, QSizeF(0, 0)},
            QPen{zoom_color, zoom_ratio});

        zoom_rect_->setVisible(true);
        zoom_rect_->setZValue(zoom_rect_zvalue);
        repaint();
        break;
    }

    default:        
        break;
    }
}

void MapView::mouseReleaseEvent(QMouseEvent* event) {
    QGraphicsView::mouseReleaseEvent(event);

    is_pressed_ = false;
    pressed_scene_point_ = {};
    last_point_ = {};    

    setCursor(Qt::ArrowCursor);
    auto map_scene = mapScene();

    switch (mode_) {
    case Mode::Zoom:
        Q_ASSERT(zoom_rect_ != nullptr);
        fitInView(zoom_rect_->rect(), Qt::KeepAspectRatio);

        map_scene->removeItem(zoom_rect_);
        zoom_rect_ = nullptr;

        repaint();        
        break;

    case Mode::Pan:
        // Fall through to let selected items to display properties in the
        // Pan mode.
        break;
    default:
        break;
    }
}


void MapView::mouseMoveEvent(QMouseEvent* event) {
    QGraphicsView::mouseMoveEvent(event);

    auto pos = mapToScene(event->pos());
    int x = pos.x();
    int y = pos.y();

    // Set status text with coordinates
    mainView()->setStatusText(QString::number(x) + "," + QString::number(y));

    if (!is_pressed_)
        return;
    
    switch (mode_) {
    case Mode::Pan: {
        if(last_scene_rect_.isNull())
            last_scene_rect_ = scene()->sceneRect();

        auto ps = mapToScene(last_point_);
        auto ts = mapToScene(event->pos());

        auto dx = ts.x() - ps.x();
        auto dy = ts.y() - ps.y();
        auto rc = last_scene_rect_;

        rc.translate(-dx, -dy);
        last_scene_rect_ = rc;

        setSceneRect(rc);
        repaint();
        break;
    }

    case Mode::Zoom: {
        auto ps = pressed_scene_point_;
        auto ts = mapToScene(event->pos());

        auto dx = ts.x() - ps.x();
        auto dy = ts.y() - ps.y();

        Q_ASSERT(zoom_rect_ != nullptr);
        zoom_rect_->setRect(QRectF(pressed_scene_point_, QSizeF(dx, dy)));
        repaint();
        break;
    }

    default:
        break;
    }

    last_point_ = event->pos();
}

void MapView::selectItem(const QPoint& pos) {
    auto selected_items = items(pos);
    auto selected_item = static_cast<MetaLayerItem*>(nullptr);

    for (auto item : selected_items) {
        selected_item = MetaLayerItem::item_cast(item);
        if (selected_item)           
            break;
    }

    if (selected_item) {
        // Clear previous selection of meta model layer items.
        clearSelection();

        selected_items_.emplace_back(selected_item);

        prop_model_ = std::make_unique<MetaItemPropertyModel>
            (selected_item->properties(), this);

        main_view_->setTableModel(prop_model_.release());
    }
}

void MapView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);

    if (mode_ == Mode::FitToView)
        zoomToFit();
}


} // namespace WaterwAIs {