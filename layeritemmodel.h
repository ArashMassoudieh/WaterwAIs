#ifndef LAYERITEMMODEL_H
#define LAYERITEMMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include "layer.h"

class LayerItemModel : public QAbstractListModel
{
    Q_OBJECT
    QList<std::shared_ptr<Layer>> layers;
    QNetworkAccessManager nam;

public:
    explicit LayerItemModel(QObject *parent = nullptr);
    void addRow(std::shared_ptr<Layer> layer);

    size_t getCount() const {
        return layers.size();
    }

    std::shared_ptr<Layer> operator [] (int index) {
        return layers[index];
    }

signals:

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    // QAbstractItemModel interface
public:
    virtual Qt::DropActions supportedDropActions() const override;

    // QAbstractItemModel interface
public:
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    // QAbstractItemModel interface
public:
    virtual QStringList mimeTypes() const override;

    // QAbstractItemModel interface
public:
    virtual QMimeData *mimeData(const QModelIndexList &indexes) const override;

    // QAbstractItemModel interface
public:
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
};

#endif // LAYERITEMMODEL_H
