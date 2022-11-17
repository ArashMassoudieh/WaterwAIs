/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSplitter>
#include <QUrl>
#include "modellayer.h"
#include "node.h"
#include <QDebug>


#include "Common.h"

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


    //QJsonDocument ModelJsonDoc = loadJson("/Users/arash/Projects/QMapViewer/resources/Example_input.json");
    //Model->GetFromJsonDocument(ModelJsonDoc);

    QPen pen;
    pen.setColor(QColor(255,0,0));
    qDebug()<<pen.color();
    pen.setWidth(3);

    for (size_t i=0; i<layers.getCount(); i++)
    {
        if (DownloadMode == downloadmode::localfile)
        {
            QFile layerfile("/mnt/3rd900/Projects/QMapViewer/HickeyRunSewer.geojson");
            if (layerfile.exists())
            {
                qDebug()<<"File '"<<layerfile.fileName() << "' exists!";
            }
            else
            {
                QMessageBox::about(this,"File not found","File "+layerfile.fileName()+" not found");
                qDebug()<<"File '"<<layerfile.fileName() << "' does not exist!";
            }
            layers[i]->JsonDoc = loadJson(QString("/mnt/3rd900/Projects/QMapViewer/HickeyRunSewer.geojson"));
            layers[i]->GetFromJsonDocument(layers[i]->JsonDoc);
            populateScene();
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

    Node *node = new Node(view->view());
    node->setX(327946.519);
    node->setY(4309540.126);
    node->setWidth(200);
    node->setHeight(200);
    node->setZValue(9000);
    scene->addItem(node);
    setWindowTitle(tr("Map viewer"));
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
