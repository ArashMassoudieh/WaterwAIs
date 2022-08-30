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

#include "segment.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSplitter>
#include <QUrl>



MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), scene(new MapScene(this))
    , h1Splitter(new QSplitter(this)), h2Splitter(new QSplitter(this))
{


    QPen pen;
    pen.setColor(QColor(255,0,0));
    qDebug()<<pen.color();
    pen.setWidth(3);
    layer.SetPen(pen);
    if (DownloadMode == downloadmode::localfile)
    {   QFile layerfile("/mnt/3rd900/Projects/QMapViewer/HickeyRunSewer.geojson");
        if (layerfile.exists())
        {
            qDebug()<<"File '"<<layerfile.fileName() << "' exists!";
        }
        else
        {
            QMessageBox::about(this,"File not found","File "+layerfile.fileName()+" not found");
            qDebug()<<"File '"<<layerfile.fileName() << "' does not exist!";
        }
        JsonDoc = loadJson(QString("/mnt/3rd900/Projects/QMapViewer/HickeyRunSewer.geojson"));
        layer.GetFromJsonDocument(JsonDoc);
        populateScene();

    }
    else if (DownloadMode == downloadmode::url)
    {
        connect (&downloader,SIGNAL(downloadfinished()),this,SLOT(OnDownloadFinished()));
        downloader.doDownload(QUrl("http://ec2-54-189-78-100.us-west-2.compute.amazonaws.com/files/Centroids.geojson"));
    }

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);

    view = new View("Map");

    view->view()->setScene(scene);

    h1Splitter->addWidget(view);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);

    setWindowTitle(tr("Map viewer"));
    ZoomAll();




}

void MainWindow::populateScene()
{
    // Populate scene
    scene->AppendLayer(&layer);
}

QJsonDocument loadJson(const QString &fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
};

QJsonDocument loadJson(QNetworkReply* fileName) {
    QByteArray data = fileName->readAll();
    qDebug()<<fileName->header(QNetworkRequest::KnownHeaders());
    return QJsonDocument().fromJson(data);
};


void MainWindow::ZoomAll()
{   //QRectF newRect = scene->itemsBoundingRect();

    QRectF newRect = layer.GetBoundingRect();
    float width = float(newRect.width());
    float height = float(newRect.height());

    if (width>scene->width() || height>scene->sceneRect().height())
        scene->setSceneRect(newRect);
    view->view()->fitInView(newRect,Qt::KeepAspectRatio);
    view->view()->repaint();
}

void MainWindow::OnDownloadFinished()
{
    qDebug()<<"Download Finished!";
    JsonDoc = loadJson(downloader.Downloaded);
    layer.GetFromJsonDocument(JsonDoc);
    populateScene();
    ZoomAll();
}
