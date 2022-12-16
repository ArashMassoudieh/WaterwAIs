#include "modellayer.h"
#include <QJsonObject>
#include <QGraphicsScene>


ModelLayer::ModelLayer():Layer()
{
    auto obj = std::make_shared<Layer>();
    //obj->AppendToFeatures()

}

//ModelLayer::ModelLayer(GraphicsView *_parent):Object()
//{

//    parent = _parent;
//    setFlag(ItemIsSelectable);
//    setAcceptHoverEvents(true);
//    setCacheMode(DeviceCoordinateCache);
//    setZValue(this->zValue());
//    parent->scene()->addItem(this);
//}

ModelLayer& ModelLayer::operator=(const ModelLayer& other)
{
    Layer::operator=(other);
    nodes = other.nodes;

    return *this;
}
ModelLayer::~ModelLayer()
{
    nodes.clear();

}
ModelLayer::ModelLayer(const ModelLayer& other):Layer(other)
{
    nodes = other.nodes;
}
bool ModelLayer::GetFromJsonDocument(const QJsonDocument &JsonDoc)
{
    //parsingMetaModelData(JsonDoc);  //This function is under implementation

    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);

        VariableList varlist = VariableList(value.toObject());
        metamodel->operator[](key) = varlist;
        Object obj(key, value.toObject());
        nodes[key] = obj;
    }
    return true;
}

bool ModelLayer :: prepareNodes(const QJsonDocument &ModelJsonDoc1)
{
    QJsonObject pointvalArray = ModelJsonDoc1.object();
        for (QJsonObject::Iterator it= pointvalArray.begin();it!=pointvalArray.end(); it++)
        {

                qDebug()<<"File '"<<it.key() << "' exists!";
                qDebug()<<it.value();
                double xCoordinate = it.value().toObject().value("x").toDouble();
                double yCoordinate = it.value().toObject().value("y").toDouble();

                Node node(it.key(),it.value().toObject());
                //node.setCursor(QCursor(clickeme()));
                node.SetName(it.key());
                node.SetComponentType(it.value().toObject().value("type").toString());
                node.setX(xCoordinate);
                node.setY(yCoordinate);
                node.setWidth(200);
                node.setHeight(200);
                node.setZValue(40000);
                node.SetMetaModel(metamodel);
               nodes[it.key()] =node;
            }
        return true;
}

void ModelLayer :: clickeme(){


}

bool ModelLayer :: AddToScene(QGraphicsScene *scene)
{
    SetScene(static_cast<MapScene*>(scene));
    for (QMap<QString,Node>::Iterator it=nodes.begin(); it!=nodes.end(); it++)
        scene->addItem(&it.value());

    return true;
}

bool ModelLayer :: parsingMetaModelData(const QJsonDocument &JsonDoc)
{
    //This is comparision logic between metamodel data and model layer data, still going on
    MetaModel* metaModelJSonData = metamodel;
    if(metaModelJSonData != nullptr)
    {
        QJsonObject JsonObject = JsonDoc.object();
        foreach(const QString& key, JsonObject.keys())
        {
            QJsonValue subValues = JsonObject.value(key);

            VariableList varlist = VariableList(subValues.toObject());
            metamodel->operator[](key) = varlist;

            foreach(const QString& k, subValues.toObject().keys())
            {
                QString values = subValues[k].toString();
                //need to check type of values as we are not getting x and y values into map
                modelDataMap.insert(k, values);
            }

        }

        QMap<QString, QString> metaData = metamodel->metaDataMap;
        QMap<QString,QString> modelData = modelDataMap;

        for(const auto& k: modelData.keys())
        {
            for(const auto& mkey: metaData.keys())
            {
                if(k.contains(mkey)){
                    QString val = modelData[k];
                    sortedNodeDataMap.insert(k, val);
//                    qDebug()<<"-----------------------------";
//                    qDebug()<<"Key = "<<k<<"Value = "<<val;
//                    qDebug()<<"-----------------------------";
                }
            }
        }
    }

    return true;
}
