/********************************************************************************
** Form generated from reading UI file 'panel.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Panel
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelIcon;
    QLabel *labelTitle;
    QToolButton *btnExpand;
    QToolButton *btnCollapse;
    QToolButton *btnClose;
    QFrame *placeholder;

    void setupUi(QFrame *Panel)
    {
        if (Panel->objectName().isEmpty())
            Panel->setObjectName("Panel");
        Panel->resize(430, 300);
        Panel->setFrameShape(QFrame::StyledPanel);
        verticalLayout = new QVBoxLayout(Panel);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, -1, -1, 2);
        labelIcon = new QLabel(Panel);
        labelIcon->setObjectName("labelIcon");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelIcon->sizePolicy().hasHeightForWidth());
        labelIcon->setSizePolicy(sizePolicy);
        labelIcon->setMaximumSize(QSize(16, 16777215));
        labelIcon->setFrameShape(QFrame::NoFrame);
        labelIcon->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(labelIcon);

        labelTitle = new QLabel(Panel);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAutoFillBackground(true);
        labelTitle->setFrameShape(QFrame::NoFrame);
        labelTitle->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(labelTitle);

        btnExpand = new QToolButton(Panel);
        btnExpand->setObjectName("btnExpand");

        horizontalLayout->addWidget(btnExpand);

        btnCollapse = new QToolButton(Panel);
        btnCollapse->setObjectName("btnCollapse");

        horizontalLayout->addWidget(btnCollapse);

        btnClose = new QToolButton(Panel);
        btnClose->setObjectName("btnClose");

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);

        placeholder = new QFrame(Panel);
        placeholder->setObjectName("placeholder");
        placeholder->setFrameShape(QFrame::StyledPanel);
        placeholder->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(placeholder);

        verticalLayout->setStretch(1, 1);

        retranslateUi(Panel);

        QMetaObject::connectSlotsByName(Panel);
    } // setupUi

    void retranslateUi(QFrame *Panel)
    {
        Panel->setWindowTitle(QCoreApplication::translate("Panel", "Form", nullptr));
        labelIcon->setText(QString());
        labelTitle->setText(QCoreApplication::translate("Panel", "Text", nullptr));
#if QT_CONFIG(tooltip)
        btnExpand->setToolTip(QCoreApplication::translate("Panel", "Expands the panel", nullptr));
#endif // QT_CONFIG(tooltip)
        btnExpand->setText(QCoreApplication::translate("Panel", "...", nullptr));
#if QT_CONFIG(tooltip)
        btnCollapse->setToolTip(QCoreApplication::translate("Panel", "Collapses the panel.", nullptr));
#endif // QT_CONFIG(tooltip)
        btnCollapse->setText(QCoreApplication::translate("Panel", "...", nullptr));
#if QT_CONFIG(tooltip)
        btnClose->setToolTip(QCoreApplication::translate("Panel", "Closes this panel", nullptr));
#endif // QT_CONFIG(tooltip)
        btnClose->setText(QCoreApplication::translate("Panel", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Panel: public Ui_Panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
