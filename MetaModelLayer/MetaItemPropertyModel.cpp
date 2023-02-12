
#include "MetaItemPropertyModel.h"
#include <MetaModelLayer/MetaLayerItem.h>

#include <QToolButton>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// PropModel

MetaItemPropertyModel::MetaItemPropertyModel(const MetaLayerItem& layer_item,
    QObject* parent):
    QAbstractTableModel(parent) {    
    setHeaderData(0, Qt::Horizontal, tr("Property"));
    setHeaderData(1, Qt::Horizontal, tr("Value"));

    buildProperies(layer_item);
}

void MetaItemPropertyModel::buildProperies(const MetaLayerItem& layer_item) {
    properties_.clear();

    for (auto& [name, value] : layer_item.properties().vars())
        properties_.emplace_back(value.type(), name, value.toString());

    auto component_name = layer_item.modelItem().component().name();
    item_name_ = layer_item.modelItem().name().toString();

    item_label_ = "<b>" + item_name_ + "</b> (" + component_name + ")";
}


int MetaItemPropertyModel::rowCount(const QModelIndex& /*parent*/) const {
    return static_cast<int>(properties_.size());
}

int MetaItemPropertyModel::columnCount(const QModelIndex& /*parent*/) const {
    return 2;
}

QVariant MetaItemPropertyModel::data(const QModelIndex& index, int role) const {
    using Type = Variable::Type;

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
            return properties_[index.row()].name;
        if (index.column() == 1) {
            auto& prop = properties_[index.row()];

            if (prop.validTimeSeries())
                return QStringLiteral("<time series>");

            return prop.value;
        }
    }

    if (role == Qt::UserRole) {
        return index.row();      
    }

    return QVariant();
}

QVariant MetaItemPropertyModel::headerData
    (int section, Qt::Orientation orientation, int role) const {
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

} // namespace WaterwAIs
