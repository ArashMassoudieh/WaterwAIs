/********************************************************************************
** Form generated from reading UI file 'mainview.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "UI/MapView.h"
#include "UI/Panel.h"

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *map_layers_splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_layers;
    QListView *lstLayers;
    WaterwAIs::Panel *propertyPanel;
    QSplitter *panel_splitter;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    WaterwAIs::MapView *mapView;
    WaterwAIs::Panel *panelWidget;

    void setupUi(QWidget *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName("MainView");
        MainView->resize(687, 596);
        verticalLayout_3 = new QVBoxLayout(MainView);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        map_layers_splitter = new QSplitter(MainView);
        map_layers_splitter->setObjectName("map_layers_splitter");
        map_layers_splitter->setOrientation(Qt::Horizontal);
        map_layers_splitter->setChildrenCollapsible(false);
        layoutWidget = new QWidget(map_layers_splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        gridLayout_layers = new QGridLayout(layoutWidget1);
        gridLayout_layers->setObjectName("gridLayout_layers");
        gridLayout_layers->setContentsMargins(0, 0, 0, 0);
        lstLayers = new QListView(layoutWidget1);
        lstLayers->setObjectName("lstLayers");
        lstLayers->setContextMenuPolicy(Qt::CustomContextMenu);
        lstLayers->setAcceptDrops(true);
        lstLayers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstLayers->setDragEnabled(true);
        lstLayers->setDragDropMode(QAbstractItemView::DragDrop);
        lstLayers->setDefaultDropAction(Qt::IgnoreAction);
        lstLayers->setAlternatingRowColors(true);

        gridLayout_layers->addWidget(lstLayers, 0, 0, 1, 1);

        splitter->addWidget(layoutWidget1);
        propertyPanel = new WaterwAIs::Panel(splitter);
        propertyPanel->setObjectName("propertyPanel");
        splitter->addWidget(propertyPanel);

        verticalLayout->addWidget(splitter);

        map_layers_splitter->addWidget(layoutWidget);
        panel_splitter = new QSplitter(map_layers_splitter);
        panel_splitter->setObjectName("panel_splitter");
        panel_splitter->setOrientation(Qt::Vertical);
        layoutWidget2 = new QWidget(panel_splitter);
        layoutWidget2->setObjectName("layoutWidget2");
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mapView = new WaterwAIs::MapView(layoutWidget2);
        mapView->setObjectName("mapView");

        gridLayout->addWidget(mapView, 0, 0, 1, 1);

        panel_splitter->addWidget(layoutWidget2);
        panelWidget = new WaterwAIs::Panel(panel_splitter);
        panelWidget->setObjectName("panelWidget");
        panel_splitter->addWidget(panelWidget);
        map_layers_splitter->addWidget(panel_splitter);

        verticalLayout_3->addWidget(map_layers_splitter);


        retranslateUi(MainView);

        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QWidget *MainView)
    {
        MainView->setWindowTitle(QCoreApplication::translate("MainView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
