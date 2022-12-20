#ifndef PropModel_H
#define PropModel_H

#include <QAbstractTableModel>
#include <QMap>
#include <variablelist.h>

class PropModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit PropModel(VariableList *variable_list = nullptr, QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;;
    void SetVariableList(VariableList *varlist) {variable_list = varlist;}
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    VariableList * GetVariableList() {return variable_list;}
private:
    VariableList *variable_list = nullptr;

};
#endif // PropModel_H
