
#include "PolygonLayerItem.h"

#include <QRandomGenerator>

namespace WaterwAIs {

namespace {
    
}


//////////////////////////////////////////////////////////////////////////
// PolygonLayerItem

PolygonLayerItem::PolygonLayerItem(const LayerGraphicsSettings& gsettings,
    const QPolygonF& polygon, bool randomize_color)
    : LayerPolyItem{gsettings}, randomize_color_{randomize_color} {
    setPolygon(polygon);
}

void PolygonLayerItem::setColors() {
    auto brush = settings_.brush;
    auto base_color = brush.color();

    if (base_color_ != base_color) {
        base_color_ = base_color;
        color_      = base_color_;

        if (randomize_color_) {
            static auto lighter = false;
                //QRandomGenerator::global()->bounded(0, 1) ? true : false;
            
            if (lighter) {
                auto delta = QRandomGenerator::global()->bounded(101, 125);
                color_ = color_.lighter(delta);
            } else {
                auto delta = QRandomGenerator::global()->bounded(110, 150);
                color_ = color_.darker(delta);
            }
            lighter = !lighter;
        }
    }
}

void PolygonLayerItem::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option, QWidget*) {
    //onPaint(painter, option);
    
    // Pen
    painter->setPen(settings_.pen);

    // Color
    setColors();

    auto fill_color = (option->state & QStyle::State_Selected)
        ? color_.darker(selected_darker) : color_;

    if (option->state & QStyle::State_MouseOver)
        fill_color = fill_color.lighter(mouse_over_lighter);

    auto brush = settings_.brush;
    brush.setColor(fill_color);

    painter->setBrush(brush);

    setPen  (painter->pen());
    setBrush(painter->brush());    

    LayerPolyItem::paint(painter, option);
}

} // namespace WaterwAIs