#include "mapscene.h"
#include "segment.h"
#include "Circle.h"
MapScene::MapScene()
{

}

MapScene::MapScene(QObject *qwidget):QGraphicsScene(qwidget)
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
                item->SetPen(layer->Pen());
                item->SetColor(layer->Pen().color());
                addItem(item);
            }
            else if (layer->GetFeatureType()==_FeatureType::Point)
            {   Circle*item = new Circle(static_cast<Circle*>(Items[i][j].get()));
                item->SetPen(layer->Pen());
                item->SetColor(layer->Pen().color());
                addItem(item);
            }
        }
    }

}
