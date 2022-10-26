#include <QPainter>
#include "layer.h"
#include "layeritemdelegate.h"

LayerItemDelegate::LayerItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void LayerItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    auto d = index.data();
    auto layer = qvariant_cast<Layer *>(d);

    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    if (!opt.decorationSize.isEmpty()) {
        painter->drawImage(QRect(opt.rect.topLeft() + QPoint(10, 0), opt.decorationSize), layer->layerIcon().toImage());
    }

    QRect rc = opt.rect;
    rc.adjust(opt.decorationSize.width() + 20, 0, 0, 0);
    if (option.state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::white));
    } else {
        painter->setPen(QPen(Qt::black));
    }
    painter->drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, layer->layerName());
    painter->restore();
}
