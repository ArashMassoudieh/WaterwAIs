
#include "Layer.h"
#include "LayerItemDelegate.h"

#include <QPainter>

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// LayerItemDelegate

LayerItemDelegate::LayerItemDelegate(QObject* parent)
    : QStyledItemDelegate{parent} {
}

void LayerItemDelegate::paint(QPainter* painter, 
    const QStyleOptionViewItem& option, const QModelIndex& index) const {
    
    auto opt = QStyleOptionViewItem{option};
    initStyleOption(&opt, index);

    auto d = index.data();
    auto layer = qvariant_cast<Layer*>(d);

    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    if (!opt.decorationSize.isEmpty()) {
        auto constexpr icon_offset_x = 10;

        painter->drawImage(QRect{opt.rect.topLeft() + QPoint(icon_offset_x, 0),
            opt.decorationSize}, layer->icon().toImage());
    }

    auto constexpr text_offset_x = 20;

    auto rc = opt.rect;
    rc.adjust(opt.decorationSize.width() + text_offset_x, 0, 0, 0);

    if (option.state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::white));
    } else {
        painter->setPen(QPen(Qt::black));
    }
    painter->drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, layer->name());
    painter->restore();    
}

} // namespace WaterWays