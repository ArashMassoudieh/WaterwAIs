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
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QString ComponentType = JsonObject.value(key).toObject()["type"].toString();
        VariableList variables = metamodel->operator[](ComponentType);
        QJsonValue value = JsonObject.value(key);

        Object obj(key, ComponentType, variables);

        foreach (const QString& variablekey, JsonObject.value(key).toObject().keys())
        {
            qDebug()<<JsonObject.value(key).toObject().value(variablekey);
            obj.SetValue(variablekey,JsonObject.value(key).toObject().value(variablekey).toString());
        }

        object_type objtype = metamodel->operator[](ComponentType).ObjectType();
        if (objtype==object_type::node)
        {   obj.AddXYNameVariables();
            double xCoordinate = JsonObject.value(key).toObject().value("x").toString().toDouble();
            double yCoordinate = JsonObject.value(key).toObject().value("y").toString().toDouble();
            nodes[key] = obj;
            nodes[key].setX(xCoordinate);
            nodes[key].setY(yCoordinate);
            nodes[key].SetName(key);
            nodes[key].setWidth(200);
            nodes[key].setHeight(200);
            nodes[key].setZValue(40000);
            nodes[key].SetMetaModel(metamodel);
        }

    }

    foreach(const QString& key, JsonObject.keys()) {
        QString ComponentType = JsonObject.value(key).toObject()["type"].toString();
        VariableList variables = metamodel->operator[](ComponentType);
        QJsonValue value = JsonObject.value(key);

        Object obj(key, ComponentType, variables);

        foreach (const QString& variablekey, JsonObject.value(key).toObject().keys())
        {
            qDebug()<<JsonObject.value(key).toObject().value(variablekey);
            obj.SetValue(variablekey,JsonObject.value(key).toObject().value(variablekey).toString());
        }

        object_type objtype = metamodel->operator[](ComponentType).ObjectType();

        if (objtype==object_type::link)
        {   obj.AddNameVariable();
            if (nodes.count(JsonObject.value(key).toObject().value("from").toString())==1 && nodes.count(JsonObject.value(key).toObject().value("to").toString())==1)
            {
                DTNode *fromnode = &nodes[JsonObject.value(key).toObject().value("from").toString()];
                DTNode *tonode = &nodes[JsonObject.value(key).toObject().value("to").toString()];
                obj.AddNameVariable();
                edges[key] = obj;
                edges[key].SetConnectedNode(fromnode, connected::from);
                edges[key].SetConnectedNode(tonode, connected::to);
                edges[key].SetName(key);
                edges[key].setZValue(40000);
                edges[key].SetMetaModel(metamodel);
            }

        }
    }
    return true;
}

bool ModelLayer :: AddToScene(QGraphicsScene *scene)
{
    SetScene(static_cast<MapScene*>(scene));
    for (QMap<QString,DTNode>::Iterator it=nodes.begin(); it!=nodes.end(); it++)
    {   scene->addItem(&it.value());
        qDebug()<<it.value().x()<<":"<<it.value().y();
    }

    for (QMap<QString,DTEdge>::Iterator it=edges.begin(); it!=edges.end(); it++)
    {   scene->addItem(&it.value());
        it.value().adjust();
        qDebug()<<it.value().ConnectedNode(connected::from)->Name()<<":"<<it.value().ConnectedNode(connected::to)->Name();
    }

    return true;
}


