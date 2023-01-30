/********************************************************************************
** Form generated from reading UI file 'chartdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTDIALOG_H
#define UI_CHARTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "UI/ChartView.h"

QT_BEGIN_NAMESPACE

class Ui_ChartDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelFrom;
    QLineEdit *lineEditFrom;
    QLabel *labelTo;
    QLineEdit *lineEditTo;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonGo;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonSettings;
    WaterwAIs::ChartView *chartView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChartDialog)
    {
        if (ChartDialog->objectName().isEmpty())
            ChartDialog->setObjectName(QString::fromUtf8("ChartDialog"));
        ChartDialog->resize(575, 490);
        verticalLayout = new QVBoxLayout(ChartDialog);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(8, 8, 8, 8);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelFrom = new QLabel(ChartDialog);
        labelFrom->setObjectName(QString::fromUtf8("labelFrom"));

        horizontalLayout->addWidget(labelFrom);

        lineEditFrom = new QLineEdit(ChartDialog);
        lineEditFrom->setObjectName(QString::fromUtf8("lineEditFrom"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditFrom->sizePolicy().hasHeightForWidth());
        lineEditFrom->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEditFrom);

        labelTo = new QLabel(ChartDialog);
        labelTo->setObjectName(QString::fromUtf8("labelTo"));

        horizontalLayout->addWidget(labelTo);

        lineEditTo = new QLineEdit(ChartDialog);
        lineEditTo->setObjectName(QString::fromUtf8("lineEditTo"));
        sizePolicy.setHeightForWidth(lineEditTo->sizePolicy().hasHeightForWidth());
        lineEditTo->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEditTo);

        pushButtonReset = new QPushButton(ChartDialog);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(pushButtonReset);

        pushButtonGo = new QPushButton(ChartDialog);
        pushButtonGo->setObjectName(QString::fromUtf8("pushButtonGo"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonGo->sizePolicy().hasHeightForWidth());
        pushButtonGo->setSizePolicy(sizePolicy1);
        pushButtonGo->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(pushButtonGo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonSettings = new QPushButton(ChartDialog);
        pushButtonSettings->setObjectName(QString::fromUtf8("pushButtonSettings"));
        pushButtonSettings->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pushButtonSettings);


        verticalLayout->addLayout(horizontalLayout);

        chartView = new WaterwAIs::ChartView(ChartDialog);
        chartView->setObjectName(QString::fromUtf8("chartView"));

        verticalLayout->addWidget(chartView);

        buttonBox = new QDialogButtonBox(ChartDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(1, 1);

        retranslateUi(ChartDialog);

        QMetaObject::connectSlotsByName(ChartDialog);
    } // setupUi

    void retranslateUi(QDialog *ChartDialog)
    {
        ChartDialog->setWindowTitle(QCoreApplication::translate("ChartDialog", "Chart", nullptr));
        labelFrom->setText(QCoreApplication::translate("ChartDialog", "From:", nullptr));
        labelTo->setText(QCoreApplication::translate("ChartDialog", "To:", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonReset->setToolTip(QCoreApplication::translate("ChartDialog", "Sets the full range", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonReset->setText(QCoreApplication::translate("ChartDialog", "Res", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonGo->setToolTip(QCoreApplication::translate("ChartDialog", "Builds chart for the range", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonGo->setText(QCoreApplication::translate("ChartDialog", "Go", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSettings->setToolTip(QCoreApplication::translate("ChartDialog", "Chart settings", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSettings->setText(QCoreApplication::translate("ChartDialog", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartDialog: public Ui_ChartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTDIALOG_H
