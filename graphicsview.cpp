#include <QDebug>
#include <QMouseEvent>
#include <QPen>
#include <QColor>
#include "node.h"
#include "graphicsview.h"
#include "mapscene.h"
#include "mainwindow.h"
#include "modellayer.h"
#include "metamodel.h"
#include "QListView"



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

        for (int i=0; i<selecteditems.size(); i++) {
            if(selecteditems[i]->data(1000).toString()=="Node")
            {
                nodes.append(static_cast<Node*>(selecteditems[i]));
            }
        }

        if (nodes.size()>0){
            QStandardItemModel* model1 = new QStandardItemModel(this);
            model1->setColumnCount(2);
            model1->setHeaderData(0, Qt::Horizontal, tr("Property"));
            model1->setHeaderData(1, Qt::Horizontal, tr("Value"));
            for (QMap<QString,Variable>::Iterator prop = nodes[0]->begin(); prop != nodes[0]->end(); prop++)
            {
                QList<QStandardItem*> row;
                row.append(new QStandardItem(prop.key()));
                row.append(new QStandardItem(prop.value().GetValue())); //Still not getting value in prop.value() even after filling in variable list. Need to check
                model1->appendRow(row);
            }

            mapview->setTableModel(model1);
        }
    }


          //I am working on this code, as get value function is not working, I am collecting in some QMap and working on it.
//        if(modelLayer != nullptr)
//        {
//            QMap<QString,QString> modelDataMap = modelLayer->getSortedNodeData();

//            QStandardItemModel* model1 = new QStandardItemModel(this);
//            model1->setColumnCount(2);
//            model1->setHeaderData(0, Qt::Horizontal, tr("Property"));
//            model1->setHeaderData(1, Qt::Horizontal, tr("Value"));

//            for (QMap<QString,Variable>::Iterator prop = nodes[0]->begin(); prop != nodes[0]->end(); prop++)
//            {

//            }

//            for(const auto& mkey: modelDataMap.keys())
//            {
//                QList<QStandardItem*> row;
//                QString key = mkey;
//                QString value = modelDataMap[mkey];
//                row.append(new QStandardItem(mkey));
//                row.append(new QStandardItem(value));
//                //row.append(new QStandardItem(prop.value().GetValue()));
//                model1->appendRow(row);
//            }

//            mapview->setTableModel(model1);
//        }
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

bool GraphicsView::SetModelLayer(const QJsonDocument &ModelLayerJsonDoc, const QJsonDocument &MetaModelJsonDoc, LayerItemModel *layeritemmodel)
{
    modelLayer = std::make_shared<ModelLayer>();
    metamodel = new MetaModel(MetaModelJsonDoc);
    modelLayer->SetMetaModel(metamodel);
    modelLayer->GetFromJsonDocument(ModelLayerJsonDoc);

    layeritemmodel->addRow(modelLayer);

    //modelLayer->prepareNodes(ModelLayerJsonDoc);

    modelLayer->AddToScene(scene());


    return true;

}
