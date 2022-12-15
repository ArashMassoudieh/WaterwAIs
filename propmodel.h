#ifndef PROPMODEL_H
#define PROPMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class propmodel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit propmodel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    void setTable(QMap<QString, QString> * tableView);

private:
    QMap<QString, QString>* _tableView;
};
#endif // PROPMODEL_H
