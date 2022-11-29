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
        QJsonValue value = JsonObject.value(key);
        Object obj(value.toObject());
        nodes[key] = obj;
    }
    return true;
}

bool ModelLayer :: prepareNodes(const QString &fileName)
{

    //QJsonDocument ModelJsonDoc1 = loadJson(QString(fileName));
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    QJsonDocument ModelJsonDoc1 = QJsonDocument().fromJson(jsonFile.readAll());
    QJsonObject pointvalArray = ModelJsonDoc1.object();
    for (QJsonObject::Iterator it= pointvalArray.begin();it!=pointvalArray.end(); it++)
    {

            qDebug()<<"File '"<<it.key() << "' exists!";
            qDebug()<<it.value();
            double xCoordinate = it.value().toObject().value("x").toDouble();
            double yCoordinate = it.value().toObject().value("y").toDouble();

                Node node;
                node.SetName(it.key());
                node.setX(xCoordinate);
                node.setY(yCoordinate);
                node.setWidth(200);
                node.setHeight(200);
                node.setZValue(9000);
                nodes[it.key()] =node;
                //scene->addItem(node);
                //setWindowTitle(tr("Map viewer"));

        }
        return true;
}

bool ModelLayer :: AddToScene(QGraphicsScene *scene)
{
    for (QMap<QString,Node>::Iterator it=nodes.begin(); it!=nodes.end(); it++)
        scene->addItem(&it.value());

    return true;
}
