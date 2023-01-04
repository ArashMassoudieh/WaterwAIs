#include "propmodel.h"

PropModel::PropModel(VariableList* varlist, QObject *parent) :
    QAbstractTableModel(parent)
{
    variables = varlist;
    setHeaderData(0, Qt::Horizontal, tr("Property"));
    setHeaderData(1, Qt::Horizontal, tr("Value"));
}


int PropModel::rowCount(const QModelIndex& parent) const
{
    return variables->count();
}

int PropModel::columnCount(const QModelIndex & parent) const
{
    return 2;
}

QVariant PropModel::data(const QModelIndex& index, int role) const
{

    if (role == Qt::DisplayRole)
    {   if (index.column() == 0)
            return variables->operator[](index.row()).Name;
        if (index.column() == 1)
            return variables->operator[](index.row()).Var->GetValue();
    }

    return QVariant();
}

QVariant PropModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Property");
            case 1:
                return QString("Value");
            }
        }
    }
    return QVariant();
}

