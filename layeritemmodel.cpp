#include <QIcon>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMimeData>

#include "layeritemmodel.h"

#define DRAG_MIME_DATA "application/int"

LayerItemModel::LayerItemModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

void LayerItemModel::addRow(std::shared_ptr<Layer> layer)
{
    auto c = layers.count();
    layer->setZ(9000 - c);

    beginInsertRows(QModelIndex(), c, c);
    layers.append(layer);
    connect(layer.get(), &Layer::iconChanged, this, [this, c]() {
        emit dataChanged(index(c), index(c), QVector<int>{ Qt::DecorationRole });
    });
    endInsertRows();
}


void LayerItemModel::moveItem(int srcIndx, int dstIndx)
{
    beginResetModel();
    layers.move(srcIndx, dstIndx);
    for (size_t i=0; i<layers.size(); i++) {
        layers[i]->setZ(9000 - i);
    }
    endResetModel();
}

int LayerItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return layers.size();
}

QVariant LayerItemModel::data(const QModelIndex &index, int role) const
{
    auto r = index.row();

    switch (role) {
    case Qt::DisplayRole:
        return QVariant::fromValue(layers[r].get());

    case Qt::DecorationRole:
        return layers[r]->layerIcon();
    }

    return QVariant();
}

Qt::DropActions LayerItemModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags LayerItemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList LayerItemModel::mimeTypes() const
{
    QStringList types {
        DRAG_MIME_DATA
    };
    return types;
}

QMimeData *LayerItemModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            stream << index.row();
        }
    }

    mimeData->setData(DRAG_MIME_DATA, encodedData);
    return mimeData;
}

bool LayerItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat(DRAG_MIME_DATA))
        return false;

    if (column > 0)
        return false;

    int dstIndx;

    if (row != -1)
        dstIndx = row;
    else if (parent.isValid())
        dstIndx = parent.row();
    else
        dstIndx = rowCount(QModelIndex());

    QByteArray encodedData = data->data(DRAG_MIME_DATA);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    int rows = 0;
    int srcIndx = 0;

    if (!stream.atEnd()) {
        stream >> srcIndx;
        ++rows;
    }

    if (dstIndx >= layers.size()) {
        dstIndx = layers.size() - 1;
    }
    QMetaObject::invokeMethod(this, [this, dstIndx, srcIndx]() {
        moveItem(srcIndx, dstIndx);
    }, Qt::QueuedConnection);

    return true;
}
