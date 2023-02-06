/********************************************************************************
** Form generated from reading UI file 'mainview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
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
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnOpen;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btnMoveUp;
    QToolButton *btnMoveDown;
    QSplitter *splitter;
    QListView *lstLayers;
    WaterwAIs::Panel *propertyPanel;
    QSplitter *panel_splitter;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    WaterwAIs::MapView *mapView;
    WaterwAIs::Panel *panelWidget;

    void setupUi(QWidget *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName(QString::fromUtf8("MainView"));
        MainView->resize(688, 596);
        verticalLayout_3 = new QVBoxLayout(MainView);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        map_layers_splitter = new QSplitter(MainView);
        map_layers_splitter->setObjectName(QString::fromUtf8("map_layers_splitter"));
        map_layers_splitter->setOrientation(Qt::Horizontal);
        map_layers_splitter->setChildrenCollapsible(false);
        layoutWidget = new QWidget(map_layers_splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnOpen = new QToolButton(layoutWidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnOpen->sizePolicy().hasHeightForWidth());
        btnOpen->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(btnOpen);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnMoveUp = new QToolButton(layoutWidget);
        btnMoveUp->setObjectName(QString::fromUtf8("btnMoveUp"));

        horizontalLayout_3->addWidget(btnMoveUp);

        btnMoveDown = new QToolButton(layoutWidget);
        btnMoveDown->setObjectName(QString::fromUtf8("btnMoveDown"));

        horizontalLayout_3->addWidget(btnMoveDown);


        verticalLayout->addLayout(horizontalLayout_3);

        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        lstLayers = new QListView(splitter);
        lstLayers->setObjectName(QString::fromUtf8("lstLayers"));
        lstLayers->setContextMenuPolicy(Qt::CustomContextMenu);
        lstLayers->setAcceptDrops(true);
        lstLayers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstLayers->setDragEnabled(true);
        lstLayers->setDragDropMode(QAbstractItemView::DragDrop);
        lstLayers->setDefaultDropAction(Qt::IgnoreAction);
        lstLayers->setAlternatingRowColors(true);
        splitter->addWidget(lstLayers);
        propertyPanel = new WaterwAIs::Panel(splitter);
        propertyPanel->setObjectName(QString::fromUtf8("propertyPanel"));
        splitter->addWidget(propertyPanel);

        verticalLayout->addWidget(splitter);

        map_layers_splitter->addWidget(layoutWidget);
        panel_splitter = new QSplitter(map_layers_splitter);
        panel_splitter->setObjectName(QString::fromUtf8("panel_splitter"));
        panel_splitter->setOrientation(Qt::Vertical);
        layoutWidget1 = new QWidget(panel_splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mapView = new WaterwAIs::MapView(layoutWidget1);
        mapView->setObjectName(QString::fromUtf8("mapView"));

        gridLayout->addWidget(mapView, 0, 0, 1, 1);

        panel_splitter->addWidget(layoutWidget1);
        panelWidget = new WaterwAIs::Panel(panel_splitter);
        panelWidget->setObjectName(QString::fromUtf8("panelWidget"));
        panel_splitter->addWidget(panelWidget);
        map_layers_splitter->addWidget(panel_splitter);

        verticalLayout_3->addWidget(map_layers_splitter);


        retranslateUi(MainView);

        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QWidget *MainView)
    {
        MainView->setWindowTitle(QCoreApplication::translate("MainView", "Form", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainView", "Open", nullptr));
#if QT_CONFIG(tooltip)
        btnMoveUp->setToolTip(QCoreApplication::translate("MainView", "Moves layer up", nullptr));
#endif // QT_CONFIG(tooltip)
        btnMoveUp->setText(QCoreApplication::translate("MainView", "Up", nullptr));
#if QT_CONFIG(tooltip)
        btnMoveDown->setToolTip(QCoreApplication::translate("MainView", "Moves layer down", nullptr));
#endif // QT_CONFIG(tooltip)
        btnMoveDown->setText(QCoreApplication::translate("MainView", "Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
