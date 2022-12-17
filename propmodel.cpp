#include "propmodel.h"

PropModel::PropModel(VariableList* varlist, QObject *parent) :
    QAbstractTableModel(parent)
{
    variable_list = varlist;
    setHeaderData(0, Qt::Horizontal, tr("Property"));
    setHeaderData(1, Qt::Horizontal, tr("Value"));
}


int PropModel::rowCount(const QModelIndex& parent) const
{
    return variable_list->count();
}

int PropModel::columnCount(const QModelIndex & parent) const
{
    return 2;
}

QVariant PropModel::data(const QModelIndex& index, int role) const
{

    if (role == Qt::DisplayRole)
    {   if (index.column() == 0)
            return variable_list->operator[](index.row()).Name;
        if (index.column() == 1)
            return variable_list->operator[](index.row()).Var->GetValue();
    }

    return QVariant();
}

