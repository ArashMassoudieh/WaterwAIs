#ifndef MAPVIEW_H_8855E8A18DF92F1F
#define MAPVIEW_H_8855E8A18DF92F1F

#include <QGraphicsView>
#include <QGraphicsItem>

#include <MetaModelLayer/MetaItemPropertyModel.h>

namespace WaterwAIs {

class MainView;
class MetaItemPropertyModel;
class MapScene;

//////////////////////////////////////////////////////////////////////////
// MapView

class MapView: public QGraphicsView {
    Q_OBJECT
public:
    explicit MapView(QWidget* parent = nullptr);

    // Operation type    
    enum class Mode {
        None,
        Pan,
        Zoom,
        FitToView
    };

    // Main view
    MainView* mainView() { return main_view_; }
    void setMainView(MainView* main_view) { main_view_ = main_view; }

    // Mode
    void setMode(Mode mode) { mode_ = mode; onModeSet(); }
    Mode mode() const { return mode_; }

    void setNoneMode () { setMode(Mode::None); }
    void setMouseZoom() { setMode(Mode::Zoom); }
    void setMousePan () { setMode(Mode::Pan); }
    void setFitToView();

public slots:
    void zoomToFit();

protected:
    MapScene* mapScene() { return reinterpret_cast<MapScene*>(scene()); }

    void mousePressEvent  (QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent   (QMouseEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    // Selected items
    void selectItem(const QPoint& pos);
    void clearSelection();

private:
    class SelectedItem {
    public:
        SelectedItem(QGraphicsItem* item): item_{item}
            { if (item_) item_->setSelected(true); }

        ~SelectedItem() { if (item_) item_->setSelected(false); }
    private:
        QGraphicsItem* item_;
    };
    
    void onModeSet();    

    Mode mode_;

    bool   is_pressed_ = false;
    QPoint last_point_;
    QRectF last_scene_rect_;

    QPointF pressed_scene_point_;
    QGraphicsRectItem* zoom_rect_;

    double font_factor_ = 1;
    MainView* main_view_ = nullptr;

    std::vector<SelectedItem> selected_items_;

    // Models  
    std::unique_ptr<MetaItemPropertyModel> prop_model_;
};

} // namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
#endif // MAPVIEW_H_8855E8A18DF92F1F
