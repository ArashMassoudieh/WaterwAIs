#ifndef GENERICITEMLISTMODEL_H_8259EF93A9A0F406
#define GENERICITEMLISTMODEL_H_8259EF93A9A0F406

#include <QStandardItemModel>

namespace WaterwAIs {

namespace MetaLayerModelItems {
class GenericItem;
}

class MetaLayerModel;

//////////////////////////////////////////////////////////////////////////
// GenericItemListModel

class GenericItemListModel: public QStandardItemModel {
public:
    using GenericItem = MetaLayerModelItems::GenericItem;

    GenericItemListModel(const MetaLayerModel& model, 
        QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;

    const GenericItem* getItem(const QModelIndex& index);

private:
    void buildModel();

    const MetaLayerModel& model_;
};


} // namespace WaterwAIs


//////////////////////////////////////////////////////////////////////////
#endif // GENERICITEMLISTMODEL_H_8259EF93A9A0F406