#include "propmodel.h"

propmodel::propmodel(QObject *parent) :
    QAbstractTableModel(parent), _tableView(nullptr)
{}

void propmodel::setTable(QMap<QString, QString>* tableView)
{
//    beginModelReset();
    _tableView = tableView;
//    endModelReset();
}

int propmodel::rowCount(const QModelIndex& parent) const
{
    if (_tableView)
        return _tableView->count();
    return 0;
}

int propmodel::columnCount(const QModelIndex & parent) const
{
    return 2;
}

QVariant propmodel::data(const QModelIndex& index, int role) const
{
//    if (!_map || !index.isValid() || index.row() >= _map->count() || role != Qt::DisplayRole)
//        return QVariant();

    auto it = _tableView->cbegin();
    it += index.row();

    if (index.column() == 0)
        return it.key();
    if (index.column() == 1)
        return it.value();

    return QVariant();
}

