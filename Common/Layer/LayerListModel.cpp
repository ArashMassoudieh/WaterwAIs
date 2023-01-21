
#include "LayerListModel.h"

#include <QIcon>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMimeData>

#include "Layer.h"

namespace WaterWays {

#define DRAG_MIME_DATA "application/int"

namespace {

constexpr auto z_value_bottom = 9000;
} // anonymous


//////////////////////////////////////////////////////////////////////////
// LayerItemModel

LayerListModel::LayerListModel(QObject* parent)
    : QAbstractListModel{parent} {
}

void LayerListModel::addLayer(LayerPtr layer) {
    auto c = layers_.count();
    layer->setZValue(z_value_bottom - c);

    beginInsertRows(QModelIndex(), c, c);
    layers_.append(layer);

    auto layer_model = layer->model();
    Q_ASSERT(layer_model);

    connect(layer_model.get(), &LayerModel::iconLoaded, this, [this, c]() {
        emit dataChanged(index(c), index(c), QVector<int>{Qt::DecorationRole});
    });
    endInsertRows();
}

void LayerListModel::moveLayer(int src_idx, int dst_idx) {
    beginResetModel();
    layers_.move(src_idx, dst_idx);

    for (auto i = 0; i < layers_.size(); i++)
        layers_[i]->setZValue(z_value_bottom - i);
    
    endResetModel();
}

int LayerListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;    

    return layers_.size();
}

QVariant LayerListModel::data(const QModelIndex& index, int role) const {
    auto row = index.row();

    switch (role) {
    case Qt::DisplayRole:
        return QVariant::fromValue(layers_[row].get());

    case Qt::DecorationRole:
        return QPixmap{layers_[row]->icon()};
    }
    return {};
}

Qt::DropActions LayerListModel::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags LayerListModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList LayerListModel::mimeTypes() const {
    auto types = QStringList {
        DRAG_MIME_DATA
    };
    return types;
}

QMimeData* LayerListModel::mimeData(const QModelIndexList& indexes) const {
    auto mime_data = new QMimeData{};
    auto encoded_data = QByteArray{};

    auto stream = QDataStream{&encoded_data, QIODevice::WriteOnly};

    for(auto& index : indexes) {
        if (index.isValid())
            stream << index.row();
    }
    mime_data->setData(DRAG_MIME_DATA, encoded_data);
    return mime_data;
}

bool LayerListModel::dropMimeData(const QMimeData* data, Qt::DropAction action,
    int row, int column, const QModelIndex& parent) {
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat(DRAG_MIME_DATA))
        return false;

    if (column > 0)
        return false;

    auto dst_idx = 0;

    if (row != -1)
        dst_idx = row;
    else if (parent.isValid())
        dst_idx = parent.row();
    else
        dst_idx = rowCount(QModelIndex());

    auto encoded_data = data->data(DRAG_MIME_DATA);
    
    auto rows = 0;
    auto srcIndx = 0;

    if (auto stream = QDataStream{&encoded_data, QIODevice::ReadOnly};
        !stream.atEnd()) {
        stream >> srcIndx;
        ++rows;
    }

    if (dst_idx >= layers_.size()) {
        dst_idx = layers_.size() - 1;
    }
    QMetaObject::invokeMethod(this, [this, dst_idx, srcIndx]() {
        moveLayer(srcIndx, dst_idx);
        }, Qt::QueuedConnection);

    return true;
}

} // namespace WaterWays