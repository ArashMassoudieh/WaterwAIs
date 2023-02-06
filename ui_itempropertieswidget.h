/********************************************************************************
** Form generated from reading UI file 'itempropertieswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMPROPERTIESWIDGET_H
#define UI_ITEMPROPERTIESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ItemPropertiesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QLineEdit *edtFilter;

    void setupUi(QFrame *ItemPropertiesWidget)
    {
        if (ItemPropertiesWidget->objectName().isEmpty())
            ItemPropertiesWidget->setObjectName(QString::fromUtf8("ItemPropertiesWidget"));
        ItemPropertiesWidget->resize(278, 401);
        ItemPropertiesWidget->setLineWidth(0);
        verticalLayout = new QVBoxLayout(ItemPropertiesWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(ItemPropertiesWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setDefaultSectionSize(24);

        verticalLayout->addWidget(tableView);

        edtFilter = new QLineEdit(ItemPropertiesWidget);
        edtFilter->setObjectName(QString::fromUtf8("edtFilter"));

        verticalLayout->addWidget(edtFilter);


        retranslateUi(ItemPropertiesWidget);

        QMetaObject::connectSlotsByName(ItemPropertiesWidget);
    } // setupUi

    void retranslateUi(QFrame *ItemPropertiesWidget)
    {
        ItemPropertiesWidget->setWindowTitle(QCoreApplication::translate("ItemPropertiesWidget", "Frame", nullptr));
        edtFilter->setPlaceholderText(QCoreApplication::translate("ItemPropertiesWidget", "Filter properties", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ItemPropertiesWidget: public Ui_ItemPropertiesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMPROPERTIESWIDGET_H
