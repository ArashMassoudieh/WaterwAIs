#ifndef PROPMODEL_H_87E53C98213CD87C
#define PROPMODEL_H_87E53C98213CD87C

#include <QAbstractTableModel>
#include "Variable.h"
#include <vector>

namespace WaterwAIs {

class MetaLayerItem;

//////////////////////////////////////////////////////////////////////////
// PropModel

// This class represents a table model for properties of some Meta Model
// layer item.

class MetaItemPropertyModel: public QAbstractTableModel {
    Q_OBJECT
public:
    struct PropertyInfo {
        using Type = Variable::Type;

        PropertyInfo(Type t, const QString& n, const QString& v)
            : type{t}, name{n}, value{v} {}

        Type    type = Type::NotAssigned;
        QString name;
        QString value;
    };

    explicit MetaItemPropertyModel(const MetaLayerItem& layer_item, QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
        int role) const override;
    
    QString itemLabel() const { return item_label_; }
    QString itemName () const { return item_name_; }

    const PropertyInfo& getProperty(int index) const
        { return properties_[index]; }

private:
    void buildProperies(const MetaLayerItem& layer_item);

    QString item_label_;
    QString item_name_;
    
    std::vector<PropertyInfo> properties_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////

#endif // PROPMODEL_H_87E53C98213CD87C
