
#include "MetaItemPropertyModel.h"

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// PropModel

MetaItemPropertyModel::MetaItemPropertyModel(const VariableMap& properties, QObject* parent):
    QAbstractTableModel(parent) {    
    setHeaderData(0, Qt::Horizontal, tr("Property"));
    setHeaderData(1, Qt::Horizontal, tr("Value"));

    buildProperies(properties);
}

void MetaItemPropertyModel::buildProperies(const VariableMap& properties) {
    properties_.clear();

    for (auto [name, value] : properties.vars())
        properties_.emplace_back(name, value.toString());
}


int MetaItemPropertyModel::rowCount(const QModelIndex& /*parent*/) const {
    return static_cast<int>(properties_.size());
}

int MetaItemPropertyModel::columnCount(const QModelIndex& /*parent*/) const {
    return 2;
}

QVariant MetaItemPropertyModel::data(const QModelIndex& index, int role) const {

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
            return properties_[index.row()].first;
        if (index.column() == 1)
            return properties_[index.row()].second;
    }

    return QVariant();
}

QVariant MetaItemPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Property");
            case 1:
                return QString("Value");
            }
        }
    }
    return QVariant();
}

} // namespace WaterWays