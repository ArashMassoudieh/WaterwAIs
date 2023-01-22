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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "UI/MapView.h"

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnOpen;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btnMoveUp;
    QToolButton *btnMoveDown;
    QSplitter *splitter;
    QListView *lstLayers;
    QTableView *tableView;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnZoom;
    QToolButton *btnPan;
    QToolButton *btnFitToView;
    QSpacerItem *horizontalSpacer;
    WaterwAIs::MapView *mapView;
    QLabel *statusbar;

    void setupUi(QWidget *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName(QString::fromUtf8("MainView"));
        MainView->resize(688, 596);
        verticalLayout_3 = new QVBoxLayout(MainView);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter_2 = new QSplitter(MainView);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setChildrenCollapsible(false);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
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
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMouseTracking(true);
        tableView->setAutoFillBackground(true);
        splitter->addWidget(tableView);

        verticalLayout->addWidget(splitter);

        splitter_2->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnZoom = new QToolButton(layoutWidget1);
        btnZoom->setObjectName(QString::fromUtf8("btnZoom"));
        btnZoom->setCheckable(true);

        horizontalLayout_2->addWidget(btnZoom);

        btnPan = new QToolButton(layoutWidget1);
        btnPan->setObjectName(QString::fromUtf8("btnPan"));
        btnPan->setCheckable(true);

        horizontalLayout_2->addWidget(btnPan);

        btnFitToView = new QToolButton(layoutWidget1);
        btnFitToView->setObjectName(QString::fromUtf8("btnFitToView"));
        btnFitToView->setCheckable(true);

        horizontalLayout_2->addWidget(btnFitToView);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        mapView = new WaterwAIs::MapView(layoutWidget1);
        mapView->setObjectName(QString::fromUtf8("mapView"));

        verticalLayout_2->addWidget(mapView);

        statusbar = new QLabel(layoutWidget1);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));

        verticalLayout_2->addWidget(statusbar);

        splitter_2->addWidget(layoutWidget1);

        verticalLayout_3->addWidget(splitter_2);


        retranslateUi(MainView);

        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QWidget *MainView)
    {
        MainView->setWindowTitle(QCoreApplication::translate("MainView", "Form", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainView", "Open", nullptr));
        btnMoveUp->setText(QCoreApplication::translate("MainView", "Up", nullptr));
        btnMoveDown->setText(QCoreApplication::translate("MainView", "Down", nullptr));
        btnZoom->setText(QCoreApplication::translate("MainView", "Zoom", nullptr));
        btnPan->setText(QCoreApplication::translate("MainView", "Pan", nullptr));
        btnFitToView->setText(QCoreApplication::translate("MainView", "Fit to view", nullptr));
        statusbar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
