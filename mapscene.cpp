#include "mapscene.h"
#include "segment.h"
#include "Circle.h"
#include "polygon.h"

MapScene::MapScene()
    : QGraphicsScene()
{
}

MapScene::MapScene(QObject *qwidget)
    :QGraphicsScene(qwidget)
{
}

bool MapScene::AppendLayer(Layer *layer)
{
    QVector<QVector<shared_ptr<QGraphicsItem>>> Items = layer->toGraphicItems();
    for (int i = 0; i<Items.size(); i++) {
        layer->feature(i)->ClearGraphicalObjects();
        for (int j=0; j<Items[i].size(); j++)
        {
            if (layer->GetFeatureType()==_FeatureType::MultiLineString)
            {   Segment *item = new Segment(static_cast<Segment*>(Items[i][j].get()));

                auto rc = item->boundingRect();
                updateBounding(rc);

                item->SetPen(layer->Pen());
                connect(layer, &Layer::penChanged, this, [=]() {
                    item->SetPen(layer->Pen());
                    emit requestRepaint();
                });

                item->SetColor(layer->layerColor());
                connect(layer, &Layer::colorChanged, this, [=]() {
                    item->SetColor(layer->layerColor());
                    emit requestRepaint();
                });

                item->setVisible(layer->visible());
                connect(layer, &Layer::visibleChanged, this, [=]() {
                    item->setVisible(layer->visible());
                    emit requestRepaint();
                });

                item->setOpacity(layer->layerOpacity());
                connect(layer, &Layer::opacityChanged, this, [=]() {
                    item->setOpacity(layer->layerOpacity());
                    emit requestRepaint();
                });

                item->setZValue(layer->layerZ());
                connect(layer, &Layer::zChanged, this, [=]() {
                    item->setZValue(layer->layerZ());
                    emit requestRepaint();
                });
                addItem(item);
            }
            else if (layer->GetFeatureType()==_FeatureType::Point)
            {   Circle *item = new Circle(static_cast<Circle*>(Items[i][j].get()));

                auto rc = item->boundingRect();
                updateBounding(rc);

                item->SetPen(layer->Pen());
                connect(layer, &Layer::penChanged, this, [=]() {
                    item->SetPen(layer->Pen());
                    emit requestRepaint();
                });

                item->SetColor(layer->layerColor());
                connect(layer, &Layer::colorChanged, this, [=]() {
                    item->SetColor(layer->layerColor());
                    emit requestRepaint();
                });

                item->setVisible(layer->visible());
                connect(layer, &Layer::visibleChanged, this, [=]() {
                    item->setVisible(layer->visible());
                    emit requestRepaint();
                });

                item->setOpacity(layer->layerOpacity());
                connect(layer, &Layer::opacityChanged, this, [=]() {
                    item->setOpacity(layer->layerOpacity());
                    emit requestRepaint();
                });

                item->setZValue(layer->layerZ());
                connect(layer, &Layer::zChanged, this, [=]() {
                    item->setZValue(layer->layerZ());
                    emit requestRepaint();
                });
                addItem(item);
            }
            else if (layer->GetFeatureType()==_FeatureType::MultiPolygon)
            {   Polygon *item = new Polygon(static_cast<Polygon*>(Items[i][j].get()));

                auto rc = item->boundingRect();
                updateBounding(rc);

                item->setBrush(QBrush(layer->layerColor()));
                item->setPen(layer->Pen());
                connect(layer, &Layer::penChanged, this, [=]() {
                    item->setPen(layer->Pen());
                    item->setBrush(QBrush(layer->layerColor()));
                    emit requestRepaint();
                });

                item->setVisible(layer->visible());
                connect(layer, &Layer::visibleChanged, this, [=]() {
                    item->setVisible(layer->visible());
                    emit requestRepaint();
                });

                item->setOpacity(layer->layerOpacity());
                connect(layer, &Layer::opacityChanged, this, [=]() {
                    item->setOpacity(layer->layerOpacity());
                    emit requestRepaint();
                });

                item->setZValue(layer->layerZ());
                connect(layer, &Layer::zChanged, this, [=]() {
                    item->setZValue(layer->layerZ());
                    emit requestRepaint();
                });
                addItem(item);
            }
        }
    }

    return true;
}

void MapScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

void MapScene::updateBounding(const QRectF &rc)
{
    if (_rc.isNull()) {
        _rc = rc;
        return;
    }

    if (rc.left() < _rc.left()) {
        _rc.setLeft(rc.left());
    }

    if (rc.top() < _rc.top()) {
        _rc.setTop(rc.top());
    }

    if (rc.right() > _rc.right()) {
        _rc.setRight(rc.right());
    }

    if (rc.bottom() > _rc.bottom()) {
        _rc.setBottom(rc.bottom());
    }
}
