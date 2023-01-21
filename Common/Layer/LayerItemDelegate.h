#ifndef LAYERITEMDELEGATE_H_BF8D4FCCFCBEAA37
#define LAYERITEMDELEGATE_H_BF8D4FCCFCBEAA37

#include <QObject>
#include <QStyledItemDelegate>

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// LayerItemDelegate

class LayerItemDelegate: public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit LayerItemDelegate(QObject* parent = nullptr);

    // QAbstractItemDelegate interface
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;

signals:
};

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // LAYERITEMDELEGATE_H_BF8D4FCCFCBEAA37
