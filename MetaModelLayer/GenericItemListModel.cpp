
#include "GenericItemListModel.h"
#include "MetaLayerModel.h"
#include "MetaLayerModelItem.h"

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// GenericItemListModel

GenericItemListModel::GenericItemListModel(const MetaLayerModel& model, 
    QObject* parent)
    : QStandardItemModel{parent}, model_{model} {

    // Building model
    buildModel();
}

void GenericItemListModel::buildModel() {
    auto& generic_items = model_.genericItemMap();

    for (auto& [name, item] : generic_items) {
        auto list_item = new QStandardItem{name};
        list_item->setData(QVariant::fromValue(item));

        // Downloading Meta-model component icon
        item->component().downloadIcon([list_item](const auto& pixmap) {
            list_item->setIcon(QIcon{pixmap});
        });

        appendRow(list_item);
    }
}

QVariant GenericItemListModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::ToolTipRole) {
        auto list_item = item(index.row());

        if (list_item->toolTip().isEmpty()) {
            using GenericItem = MetaLayerModelItems::GenericItem;

            // build the tooltip.
            auto generic_item = 
                qvariant_cast<GenericItem*>(index.data(Qt::UserRole + 1));

            list_item->setToolTip(generic_item->toolTip());
        }
    }
    return QStandardItemModel::data(index, role);
}

const GenericItemListModel::GenericItem* 
GenericItemListModel::getItem(const QModelIndex& index) {
    auto generic_item =
        qvariant_cast<GenericItem*>(index.data(Qt::UserRole + 1));

    return generic_item;
}


} // namespace WaterwAIs