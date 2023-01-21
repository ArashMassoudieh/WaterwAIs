#ifndef PROPMODEL_H_87E53C98213CD87C
#define PROPMODEL_H_87E53C98213CD87C

#include <QAbstractTableModel>
#include "Variable.h"
#include <vector>

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// PropModel

// This class represents a table model for properties of some Meta Model
// layer item.

class MetaItemPropertyModel: public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MetaItemPropertyModel(const VariableMap& properties, QObject* parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
        int role) const override;
    
private:
    void buildProperies(const VariableMap& properties);

    std::vector<std::pair<QString, QString>> properties_;
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////

#endif // PROPMODEL_H_87E53C98213CD87C
