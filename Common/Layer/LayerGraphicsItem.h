
#ifndef GRAPHICSITEM_H_BA695EA6F7E1499D
#define GRAPHICSITEM_H_BA695EA6F7E1499D

#include <QGraphicsItem>
#include <QPen>
#include <QPoint>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

#include <type_traits>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// LayerGraphicsSettings
// 
// Common graphics settings which layer provides to its graphics items.

class LayerGraphicsSettings {
public:
    QPen   pen   = {Qt::black};
    QBrush brush = {Qt::black};

    // Settings for selected items
    int    selected_line_width = 5;
    QColor selected_color = {Qt::darkBlue};
};

//////////////////////////////////////////////////////////////////////////
// GraphicsLayerItem
// This class provides a template for "layer" graphics items, where the layer
// provides the "pen" (color, line width etc) which the layer item should use
// for painting.
//
// It allows to easily redraw the the item when the layer changes its pen. 

template <typename T>
concept QGraphicsItemObject = std::is_base_of<QGraphicsItem, T>::value;

template<QGraphicsItemObject T>
class LayerGraphicsItem : public T {
public:
    LayerGraphicsItem(const LayerGraphicsSettings& settings)
        : settings_{settings} {
        // Making layer items selectable and accept hover events
        //T::setFlags(QGraphicsItem::ItemIsSelectable);       
        //T::setAcceptHoverEvents(true);
    }
    
    // Returns reference to the external (layer's) graphics settings used to
    // draw layer's items.
    const LayerGraphicsSettings& settings() { return settings_; }

protected:
    static constexpr int mouse_over_lighter = 125;
    static constexpr int selected_darker    = 150;
    

    // Performs some painting operations common for all layer items.
    void onPaint(QPainter* painter, const QStyleOptionGraphicsItem* option) {
        // Pen
        painter->setPen(settings_.pen);

        // Brush
        auto brush = settings_.brush;
        auto color = brush.color();

        auto fill_color = (option->state & QStyle::State_Selected)
            ? color.darker(selected_darker) : color;

        if (option->state & QStyle::State_MouseOver)
            fill_color = fill_color.lighter(mouse_over_lighter);        

        brush.setColor(fill_color);
        painter->setBrush(brush);
    }

    // Mouse moving event handlers
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        T::mousePressEvent(event);
        T::update();
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->modifiers() & Qt::ShiftModifier) {
            onItemMove(event->pos()); // Notifying item about moving
            T::update();
            return;
        }
        T::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        T::mouseReleaseEvent(event);
        T::update();
    }

    // Notification that item is about to move.
    // The 'pos' parameter provides the new item position.
    virtual void onItemMove(const QPointF& /*pos*/) {}

    const LayerGraphicsSettings&  settings_;
};

using LayerGenericItem = LayerGraphicsItem<QGraphicsItem>;
using LayerLineItem    = LayerGraphicsItem<QGraphicsLineItem>;
using LayerPolyItem    = LayerGraphicsItem<QGraphicsPolygonItem>;

} // WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // GRAPHICSITEM_H_BA695EA6F7E1499D
