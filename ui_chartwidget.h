/********************************************************************************
** Form generated from reading UI file 'chartwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTWIDGET_H
#define UI_CHARTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "UI/Chart/ChartView.h"

QT_BEGIN_NAMESPACE

class Ui_ChartWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelFrom;
    QLineEdit *lineEditFrom;
    QLabel *labelTo;
    QLineEdit *lineEditTo;
    QPushButton *pushButtonGo;
    QToolButton *toolButtonReset;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonSettings;
    WaterwAIs::ChartView *chartView;

    void setupUi(QFrame *ChartWidget)
    {
        if (ChartWidget->objectName().isEmpty())
            ChartWidget->setObjectName("ChartWidget");
        ChartWidget->resize(574, 490);
        verticalLayout = new QVBoxLayout(ChartWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelFrom = new QLabel(ChartWidget);
        labelFrom->setObjectName("labelFrom");

        horizontalLayout->addWidget(labelFrom);

        lineEditFrom = new QLineEdit(ChartWidget);
        lineEditFrom->setObjectName("lineEditFrom");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditFrom->sizePolicy().hasHeightForWidth());
        lineEditFrom->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEditFrom);

        labelTo = new QLabel(ChartWidget);
        labelTo->setObjectName("labelTo");

        horizontalLayout->addWidget(labelTo);

        lineEditTo = new QLineEdit(ChartWidget);
        lineEditTo->setObjectName("lineEditTo");
        sizePolicy.setHeightForWidth(lineEditTo->sizePolicy().hasHeightForWidth());
        lineEditTo->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEditTo);

        pushButtonGo = new QPushButton(ChartWidget);
        pushButtonGo->setObjectName("pushButtonGo");
        pushButtonGo->setMaximumSize(QSize(45, 16777215));

        horizontalLayout->addWidget(pushButtonGo);

        toolButtonReset = new QToolButton(ChartWidget);
        toolButtonReset->setObjectName("toolButtonReset");
        toolButtonReset->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(toolButtonReset);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButtonSettings = new QToolButton(ChartWidget);
        toolButtonSettings->setObjectName("toolButtonSettings");
        toolButtonSettings->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(toolButtonSettings);


        verticalLayout->addLayout(horizontalLayout);

        chartView = new WaterwAIs::ChartView(ChartWidget);
        chartView->setObjectName("chartView");

        verticalLayout->addWidget(chartView);

        verticalLayout->setStretch(1, 1);

        retranslateUi(ChartWidget);

        QMetaObject::connectSlotsByName(ChartWidget);
    } // setupUi

    void retranslateUi(QFrame *ChartWidget)
    {
        ChartWidget->setWindowTitle(QCoreApplication::translate("ChartWidget", "Chart", nullptr));
        labelFrom->setText(QCoreApplication::translate("ChartWidget", "From:", nullptr));
        labelTo->setText(QCoreApplication::translate("ChartWidget", "To:", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonGo->setToolTip(QCoreApplication::translate("ChartWidget", "Builds chart for the range", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonGo->setText(QCoreApplication::translate("ChartWidget", "Go", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonReset->setToolTip(QCoreApplication::translate("ChartWidget", "Sets the full range", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonReset->setText(QCoreApplication::translate("ChartWidget", "Res", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonSettings->setToolTip(QCoreApplication::translate("ChartWidget", "Chart settings", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonSettings->setText(QCoreApplication::translate("ChartWidget", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartWidget: public Ui_ChartWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTWIDGET_H
