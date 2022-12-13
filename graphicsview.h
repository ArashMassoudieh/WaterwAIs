#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
//#include "modellayer.h"

class MapView;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    enum OperationType {
        None,
        Pan,
        Zoom
    };
    Q_ENUM(OperationType);

    explicit GraphicsView(QWidget *parent = nullptr);
    MapView *mainWindow();
    OperationType operationType() const {
        return _type;
    }

    void setOperationType(const OperationType type) {
        _type = type;
    }

    void setMapScene(QGraphicsScene *scene);
    double FontFactor() const {return fontfactor;};
    void SetMapView(MapView* map) {mapview = map;}
    //ModelLayer *Model;

public slots:
    void zoomToFit();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

private:
    OperationType _type;
    bool _isPressed;
    QPoint _lastPoint;
    QPointF _pressedScPoint;
    QGraphicsRectItem *_rect;
    double fontfactor = 1;
    MapView* mapview = nullptr;
};

#endif // GRAPHICSVIEW_H
