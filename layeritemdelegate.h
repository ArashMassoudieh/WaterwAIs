#ifndef LAYERITEMDELEGATE_H
#define LAYERITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class LayerItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit LayerItemDelegate(QObject *parent = nullptr);

signals:


    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // LAYERITEMDELEGATE_H
