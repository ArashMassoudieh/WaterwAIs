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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelItem;
    QTableView *tableView;
    QLineEdit *edtFilter;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    WaterwAIs::MapView *mapView;

    void setupUi(QWidget *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName(QString::fromUtf8("MainView"));
        MainView->resize(689, 596);
        verticalLayout_3 = new QVBoxLayout(MainView);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter_2 = new QSplitter(MainView);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setChildrenCollapsible(false);
        layoutWidget = new QWidget(splitter_2);
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
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelItem = new QLabel(layoutWidget1);
        labelItem->setObjectName(QString::fromUtf8("labelItem"));
        labelItem->setFrameShape(QFrame::Panel);
        labelItem->setFrameShadow(QFrame::Raised);
        labelItem->setMargin(1);

        verticalLayout_4->addWidget(labelItem);

        tableView = new QTableView(layoutWidget1);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMouseTracking(true);
        tableView->setAutoFillBackground(true);
        tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setMinimumSectionSize(24);
        tableView->verticalHeader()->setDefaultSectionSize(24);
        tableView->verticalHeader()->setStretchLastSection(false);

        verticalLayout_4->addWidget(tableView);

        edtFilter = new QLineEdit(layoutWidget1);
        edtFilter->setObjectName(QString::fromUtf8("edtFilter"));

        verticalLayout_4->addWidget(edtFilter);

        splitter->addWidget(layoutWidget1);

        verticalLayout->addWidget(splitter);

        splitter_2->addWidget(layoutWidget);
        layoutWidget2 = new QWidget(splitter_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mapView = new WaterwAIs::MapView(layoutWidget2);
        mapView->setObjectName(QString::fromUtf8("mapView"));

        gridLayout->addWidget(mapView, 0, 0, 1, 1);

        splitter_2->addWidget(layoutWidget2);

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
        labelItem->setText(QCoreApplication::translate("MainView", "item", nullptr));
        edtFilter->setPlaceholderText(QCoreApplication::translate("MainView", "Filter properties", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
