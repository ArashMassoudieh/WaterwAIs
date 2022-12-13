#include "propmodel.h"
#include <QTableWidget>
#include <QTableWidgetItem>

propmodel::propmodel(QObject *parent)
    : QAbstractItemModel(parent)
{
    //setupUi(this);
}

QVariant propmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex propmodel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex propmodel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int propmodel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int propmodel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant propmodel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
