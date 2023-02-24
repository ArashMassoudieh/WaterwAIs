
#include "MetaItemPropertyModel.h"
#include <MetaModelLayer/MetaLayerItem.h>

#include <QToolButton>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// PropModel

MetaItemPropertyModel::MetaItemPropertyModel(const ModelItem& model_item,
    QObject* parent):
    QAbstractTableModel(parent) {    
    setHeaderData(0, Qt::Horizontal, tr("Property"));
    setHeaderData(1, Qt::Horizontal, tr("Value"));

    buildProperies(model_item);
}

void MetaItemPropertyModel::buildProperies(const ModelItem& model_item) {
    properties_.clear();

    for (auto& [name, value] : model_item.properties().vars()) {
        auto display_name = value.displayName();

        if (display_name.isEmpty())
            display_name = name;

        properties_.emplace_back(value.type(), display_name, value.toString(),
            value.presentationValue(), value.description());
    }

    auto component_name = model_item.component().name();
    item_name_ = model_item.name().toString();

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
            return prop.presentation;
        }
    }

    if (role == Qt::ToolTipRole) {
        auto& prop = properties_[index.row()];
        return prop.description;
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
