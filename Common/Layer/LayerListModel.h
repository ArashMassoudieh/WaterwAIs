#ifndef LAYERITEMMODEL_H_82BF23B8AEAF7EA1
#define LAYERITEMMODEL_H_82BF23B8AEAF7EA1

#include <QObject>
#include <QAbstractListModel>
#include <QIcon>
#include <memory>

namespace WaterwAIs {

class Layer;

//////////////////////////////////////////////////////////////////////////
// MessageListModel
// This model class provides a message displaying functionality in the
// list view.

class MessageListModel: public QAbstractListModel {
    Q_OBJECT
public:    
    explicit MessageListModel(QObject* parent = nullptr);    

    void setText(QStringView text, const QIcon& icon = {});

public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QString message_;
    QIcon   icon_;
};

//////////////////////////////////////////////////////////////////////////
// LayerItemModel
// This model class provides a storage and model for layers

class LayerListModel: public QAbstractListModel {
    Q_OBJECT        
public:
    using LayerPtr = std::shared_ptr<Layer>;

    explicit LayerListModel(QObject* parent = nullptr);

    // Clears the list model;
    void clear() { layers_.clear(); }

    // Adds layer to the model
    void addLayer(LayerPtr layer);

    // Moves layer from one position to another
    bool moveLayer(int from, int to);

    // Returns a number of stored layers
    size_t size() const { return layers_.size(); }

    // Returns layer pointer by index
    LayerPtr operator [] (int index) { return layers_[index]; }

signals:
    void layerMoved(int to);

public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    Qt::DropActions supportedDropActions() const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QModelIndexList& indexes) const override;

    bool dropMimeData(const QMimeData* data, Qt::DropAction action,
        int row, int column, const QModelIndex& parent) override;

private:
    QList<LayerPtr> layers_;
};

} // namespace WaterwAIs

#endif // LAYERITEMMODEL_H_82BF23B8AEAF7EA1
