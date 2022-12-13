#include <QDebug>
#include <QMouseEvent>
#include <QPen>
#include <QColor>
#include "node.h"
#include "graphicsview.h"
#include "mapscene.h"
#include "mainwindow.h"


GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    _type = OperationType::None;
    _rect = nullptr;
}

void GraphicsView::setMapScene(QGraphicsScene *scene)
{
    auto s = (MapScene *) scene;
    connect (s, &MapScene::requestRepaint, this, [this]() {
        repaint();
    });
    QGraphicsView::setScene(scene);
}

void GraphicsView::zoomToFit()
{
    auto sc = (MapScene *) scene();
    auto rc = sc->contentBoundingBox();
    fitInView(rc, Qt::KeepAspectRatio);
    repaint();
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        _isPressed = true;
        _lastPoint = event->pos();
        _pressedScPoint = mapToScene(event->pos());
    } else {
        QGraphicsView::mousePressEvent(event);
    }

    auto sc = (MapScene *) scene();

    switch (_type) {
    case OperationType::Pan:
        setCursor(Qt::ClosedHandCursor);
        break;

    case OperationType::Zoom: {
        auto rc = sc->sceneRect();
        auto zoomWRatio = qreal(rc.width()) / sc->contentBoundingBox().width();
        auto zoomHRatio = qreal(rc.height()) / sc->contentBoundingBox().height();
        auto zoomRatio = min(zoomWRatio, zoomHRatio);

        Q_ASSERT(_rect == nullptr);
        _rect = sc->addRect(
                    QRectF(_pressedScPoint, QSizeF(0, 0)),
                    QPen(QColor(100, 100, 100), zoomRatio));
        _rect->setVisible(true);
        repaint();
        break;
    }

    default:
        break;
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    _isPressed = false;
    setCursor(Qt::ArrowCursor);
    auto sc = (MapScene *) scene();

    switch (_type) {
    case OperationType::Pan: {
        break;
    }

    case OperationType::Zoom:
        Q_ASSERT(_rect != nullptr);
        fitInView(_rect->rect(), Qt::KeepAspectRatio);
        sc->removeItem(_rect);
        repaint();
        _rect = nullptr;
        break;

    default:
        QList<QGraphicsItem*> selecteditems = items(event->pos());
        QList<Node*> nodes;
        auto t = selecteditems.first();
         Node *first = dynamic_cast<Node *>(selecteditems.first());
        int _x = mapToScene(event->pos()).x();
        int _y = mapToScene(event->pos()).y();
         for (int i=0; i<selecteditems.size(); i++) {
            if(selecteditems[i]->data(1000).toString()=="Node"){
                QString fileName = "/Users/venkateshputta/WWTP-Project/QMapViewer/Json/Example_input.json";
                QFile jsonFile(fileName);
                jsonFile.open(QFile::ReadOnly);
                QJsonDocument ModelJsonDoc1 = QJsonDocument().fromJson(jsonFile.readAll());
                QJsonObject pointvalArray = ModelJsonDoc1.object();
                nodes.append(static_cast<Node*>(selecteditems[i]));
                 QString s = QString::number(_x);
                 QString s1 = QString::number(_y);
                   QString s3 = s.left(4);

                   QList<QStandardItem *> fn;

                   for (QJsonObject::Iterator it= pointvalArray.begin();it!=pointvalArray.end(); it++)
                   {

                           qDebug()<<it.value();
                           QJsonObject r = it.value().toObject();
                           int xCoordinate = it.value().toObject().value("x").toDouble();
                           int yCoordinate = it.value().toObject().value("y").toDouble();
                           QString s5 = QString::number(xCoordinate);
                           //if(s5.left(4) == s3){
                           if(s5.contains(s3)){
                               QString name = it.value().toObject().value("name").toString();
                                QString mail = it.value().toObject().value("mail").toString();
                               fn.append(new QStandardItem(name));
                               fn.append(new QStandardItem(mail));
                           }
                   }
                   QStandardItemModel* model1 = new QStandardItemModel(this);
                    model1->setColumnCount(2);
                    model1->appendRow(fn);
                    model1->setHeaderData(0, Qt::Horizontal, tr("Name"));
                    model1->setHeaderData(1, Qt::Horizontal, tr("Email"));
                  mapview->setTableModel(model1);
            }
        }
        break;
    }
}

MapView *GraphicsView::mainWindow()
{
    return mapview;
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    int _x = mapToScene(event->pos()).x();
    int _y = mapToScene(event->pos()).y();
    mainWindow()->StatusBar()->setText(QString::number(_x)+"," + QString::number(_y));

    if (!_isPressed) {
        return;
    }

    auto sc = (MapScene *) scene();

    switch (_type) {
    case OperationType::Pan: {
        static auto lastSceneRect = scene()->sceneRect();

        auto ps = mapToScene(_lastPoint);
        auto ts = mapToScene(event->pos());

        auto dx = ts.x() - ps.x();
        auto dy = ts.y() - ps.y();
        auto rc = lastSceneRect;

        rc.translate(-dx, -dy);
        lastSceneRect = rc;

        setSceneRect(rc);
        repaint();
        break;
    }

    case OperationType::Zoom: {
        auto ps = _pressedScPoint;
        auto ts = mapToScene(event->pos());

        auto dx = ts.x() - ps.x();
        auto dy = ts.y() - ps.y();

        Q_ASSERT(_rect != nullptr);
        _rect->setRect(QRectF(_pressedScPoint, QSizeF(dx, dy)));
        repaint();
        break;
    }

    default:

        break;
    }

    _lastPoint = event->pos();
}
