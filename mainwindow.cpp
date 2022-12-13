
#include "mainwindow.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSplitter>
#include <QUrl>
#include "modellayer.h"
#include <QDebug>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), scene(new MapScene(this))
    , h1Splitter(new QSplitter(this)), h2Splitter(new QSplitter(this))
{   
    auto Layer1 = std::make_shared<Layer>();
    Layer1->address=HOST_PATH "/Centroids.geojson";
    Layer1->SetColor(Qt::red);
    Layer1->SetScene(scene);
    layers.addRow(Layer1);

    auto Layer2 = std::make_shared<Layer>();
    Layer2->address=HOST_PATH "/HickeyRunSewer.geojson";
    Layer2->SetColor(Qt::blue);
    Layer2->SetScene(scene);
    layers.addRow(Layer2);

    auto Layer3 = std::make_shared<Layer>();
    Layer3->address=HOST_PATH "/PourPoints.geojson";
    Layer3->SetColor(Qt::green);
    Layer3->SetScene(scene);
    layers.addRow(Layer3);

    auto Layer4 = std::make_shared<Layer>();
    Layer4->address=HOST_PATH "/SubWaterSheds.geojson";
    Layer4->SetColor(Qt::yellow);
    Layer4->SetScene(scene);
    layers.addRow(Layer4);

    auto Layer5 = std::make_shared<Layer>();
    Layer5->address=HOST_PATH "/meta_model.json";
    Layer5->SetColor(Qt::red);
    Layer5->SetScene(scene);
    layers.addRow(Layer5);

    QPen pen;
    pen.setColor(QColor(255,0,0));
    qDebug()<<pen.color();
    pen.setWidth(3);

    for (size_t i=0; i<layers.getCount(); i++)
    {
        if (DownloadMode == downloadmode::localfile)
        {
            QString  Filename = layers[i]->address;
            QFile layerfile(Filename);
            if (layerfile.exists())
            {
                qDebug()<<"File '"<<layerfile.fileName() << "' exists!";
                layers[i]->JsonDoc = loadJson(QString(Filename));
                layers[i]->GetFromJsonDocument(layers[i]->JsonDoc);
                populateScene();
            }
            else
            {
                QMessageBox::about(this,"File not found","File "+layerfile.fileName()+" not found");
                qDebug()<<"File '"<<layerfile.fileName() << "' does not exist!";
            }
        }
        else if (DownloadMode == downloadmode::url)
        {
            layers[i]->downloader.doDownload(QUrl(layers[i]->address));
        }
    }

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);

    view = new MapView(this);

    view->setLayerListModel(&layers);
    view->view()->setMapScene(scene);
    h1Splitter->addWidget(view);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);

    setLayout(layout);

    Model = new ModelLayer();

#ifdef Arash
    QJsonDocument metamodeljason = loadJson(QString("/home/arash/Projects/QMapViewer/Json/meta_model.json"));
#else
    QJsonDocument metamodeljason = loadJson(QString("/Users/venkateshputta/WWTP-Project/QMapViewer/Json/meta_model.json"));
#endif

    MetaModel *metaModel = new MetaModel(metamodeljason);
    Model->SetMetaModel(metaModel);

#ifdef Arash
    if( Model->prepareNodes("/home/arash/Projects/QMapViewer/Json/Example_input.json"))
#else
    if( Model->prepareNodes("/Users/venkateshputta/WWTP-Project/QMapViewer/Json/Example_input.json"))
#endif
        Model->AddToScene(scene);

}

void MainWindow::populateScene()
{
    for (size_t i=0; i<layers.getCount(); i++) {
        scene->AppendLayer(layers[i].get());
    }
}

void MainWindow::zoomAll()
{
    view->view()->zoomToFit();
}

void MainWindow::OnDownloadFinished()
{
    populateScene();
    zoomAll();
}
