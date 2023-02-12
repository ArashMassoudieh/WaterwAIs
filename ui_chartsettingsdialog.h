/********************************************************************************
** Form generated from reading UI file 'chartsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTSETTINGSDIALOG_H
#define UI_CHARTSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChartSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *comboBoxTheme;
    QLabel *label_2;
    QComboBox *comboBoxLegend;
    QCheckBox *checkBoxAntiAliasing;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChartSettingsDialog)
    {
        if (ChartSettingsDialog->objectName().isEmpty())
            ChartSettingsDialog->setObjectName("ChartSettingsDialog");
        ChartSettingsDialog->resize(213, 129);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChartSettingsDialog->sizePolicy().hasHeightForWidth());
        ChartSettingsDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ChartSettingsDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(ChartSettingsDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        comboBoxTheme = new QComboBox(ChartSettingsDialog);
        comboBoxTheme->setObjectName("comboBoxTheme");

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxTheme);

        label_2 = new QLabel(ChartSettingsDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        comboBoxLegend = new QComboBox(ChartSettingsDialog);
        comboBoxLegend->setObjectName("comboBoxLegend");

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBoxLegend);


        verticalLayout->addLayout(formLayout);

        checkBoxAntiAliasing = new QCheckBox(ChartSettingsDialog);
        checkBoxAntiAliasing->setObjectName("checkBoxAntiAliasing");

        verticalLayout->addWidget(checkBoxAntiAliasing);

        buttonBox = new QDialogButtonBox(ChartSettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ChartSettingsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ChartSettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ChartSettingsDialog, qOverload<>(&QDialog::reject));
        QObject::connect(comboBoxTheme, SIGNAL(currentIndexChanged(int)), ChartSettingsDialog, SLOT(changed()));
        QObject::connect(comboBoxLegend, SIGNAL(currentIndexChanged(int)), ChartSettingsDialog, SLOT(changed()));
        QObject::connect(checkBoxAntiAliasing, SIGNAL(clicked(bool)), ChartSettingsDialog, SLOT(changed()));

        QMetaObject::connectSlotsByName(ChartSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *ChartSettingsDialog)
    {
        ChartSettingsDialog->setWindowTitle(QCoreApplication::translate("ChartSettingsDialog", "Settings", nullptr));
        label->setText(QCoreApplication::translate("ChartSettingsDialog", "Theme:", nullptr));
        label_2->setText(QCoreApplication::translate("ChartSettingsDialog", "Legend:", nullptr));
        checkBoxAntiAliasing->setText(QCoreApplication::translate("ChartSettingsDialog", "Anti-aliasing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartSettingsDialog: public Ui_ChartSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTSETTINGSDIALOG_H
