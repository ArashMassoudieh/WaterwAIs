#ifndef LAYERITEMMODEL_H_82BF23B8AEAF7EA1
#define LAYERITEMMODEL_H_82BF23B8AEAF7EA1

#include <QObject>
#include <QAbstractListModel>
#include <memory>

namespace WaterwAIs {

class Layer;

//////////////////////////////////////////////////////////////////////////
// LayerItemModel
// This model class provides a storage and model for layers

class LayerListModel: public QAbstractListModel {
    Q_OBJECT        
public:
    using LayerPtr = std::shared_ptr<Layer>;

    explicit LayerListModel(QObject* parent = nullptr);

    // Adds layer to the model
    void addLayer(LayerPtr layer);

    // Moves layer from one position to another
    bool moveLayer(int from, int to);

    // Returns a number of stored layers
    size_t size() const { return layers_.size(); }

    // Returns layer pointer by index
    LayerPtr operator [] (int index) { return layers_[index]; }    

public:
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

    virtual Qt::DropActions supportedDropActions() const override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QStringList mimeTypes() const override;
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const override;

    virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, 
        int row, int column, const QModelIndex& parent) override;

private:
    QList<LayerPtr> layers_;
};

} // namespace WaterwAIs

#endif // LAYERITEMMODEL_H_82BF23B8AEAF7EA1
