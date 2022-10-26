#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

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

    OperationType operationType() const {
        return _type;
    }

    void setOperationType(const OperationType type) {
        _type = type;
    }

    void setMapScene(QGraphicsScene *scene);

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
};

#endif // GRAPHICSVIEW_H
