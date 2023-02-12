
#include "Layer.h"
#include "LayerItemDelegate.h"

#include <QPainter>

namespace WaterwAIs {

namespace {

auto constexpr icon_offset_x = 0;//10;
auto constexpr text_offset_x = 10;

} // anonymous


//////////////////////////////////////////////////////////////////////////
// LayerItemDelegate

LayerItemDelegate::LayerItemDelegate(QObject* parent)
    : QStyledItemDelegate{parent} {
}

void LayerItemDelegate::paint(QPainter* painter, 
    const QStyleOptionViewItem& option, const QModelIndex& index) const {
    
    auto opt = QStyleOptionViewItem{option};
    initStyleOption(&opt, index);

    auto layer = qvariant_cast<Layer*>(index.data());

    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    if (!opt.decorationSize.isEmpty()) {
        auto icon_data = index.data(Qt::DecorationRole).value<QPixmap>();

        painter->drawImage(QRect{opt.rect.topLeft() + QPoint(icon_offset_x, 0),
            opt.decorationSize}, icon_data.toImage());
    }    

    auto rc = opt.rect;
    rc.adjust(opt.decorationSize.width() + text_offset_x, 0, 0, 0);

    if (option.state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::white));
    } else {
        painter->setPen(QPen(Qt::black));
    }
    painter->drawText(rc, Qt::AlignLeft | Qt::AlignVCenter, layer->displayText());
    painter->restore();    
}


} // namespace WaterwAIs