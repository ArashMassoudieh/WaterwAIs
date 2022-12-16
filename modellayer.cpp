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
        QString ComponentType = JsonObject.value(key).toObject()["type"].toString();
        VariableList variables = metamodel->operator[](ComponentType);
        QJsonValue value = JsonObject.value(key);
        Object obj(key, ComponentType, variables);

        object_type objtype = metamodel->operator[](ComponentType).ObjectType();
        if (objtype==object_type::node)
            obj.AddXYNameVariables();
        else if (objtype==object_type::link)
            obj.AddNameVariable();
        double xCoordinate = JsonObject.value(key).toObject().value("x").toString().toDouble();
        double yCoordinate = JsonObject.value(key).toObject().value("y").toString().toDouble();

        foreach (const QString& variablekey, JsonObject.value(key).toObject().keys())
        {
            qDebug()<<JsonObject.value(key).toObject().value(variablekey);
            obj.SetValue(variablekey,JsonObject.value(key).toObject().value(variablekey).toString());
        }
        nodes[key] = obj;
        nodes[key].setX(xCoordinate);
        nodes[key].setY(yCoordinate);
        nodes[key].SetName(key);
        nodes[key].setWidth(200);
        nodes[key].setHeight(200);
        nodes[key].setZValue(40000);
        nodes[key].SetMetaModel(metamodel);
    }
    return true;
}

/*
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
*/

void ModelLayer :: clickeme(){


}

bool ModelLayer :: AddToScene(QGraphicsScene *scene)
{
    SetScene(static_cast<MapScene*>(scene));
    for (QMap<QString,Node>::Iterator it=nodes.begin(); it!=nodes.end(); it++)
        scene->addItem(&it.value());

    return true;
}


