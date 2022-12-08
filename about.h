#ifndef ABOUT_H
#define ABOUT_H

#include <QAbstractItemModel>
#include <QDialog>
#include "ui_dialog.h"

class about : public QDialog , public Ui::Dialog
{
    Q_OBJECT

public:
    about(QWidget * parent = 0);

};

#endif // ABOUT_H
