#include "aboutdialog.h"

AboutDialog::AboutDialog(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant AboutDialog::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex AboutDialog::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex AboutDialog::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int AboutDialog::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int AboutDialog::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant AboutDialog::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
