
#include "NodeLayerItem.h"

namespace WaterwAIs {

namespace {
    // Default Node parameters    
static constexpr double node_width     = 200;
static constexpr double node_height    = 200;

static constexpr auto sel_adjustment   = 10;
static constexpr auto bound_adjustment = 2;
} // anonymous

//////////////////////////////////////////////////////////////////////////
// NodeLayerItem

NodeLayerItem::NodeLayerItem(const LayerGraphicsSettings& gsettings,
    NodeItem& node_item)
    : MetaLayerItem{gsettings, node_item} {    

    // Size
    auto width  = node_item.width();
    auto height = node_item.height();

    if (width > 0 && height == 0)
        height = width;

    if (height > 0 && width == 0)
        width = height;

    if (height == 0) {
        // Neither the Node item nor its component don't specify width and
        // height, so let's use the default values.
        width  = node_width;
        height = node_height;
    }

    size_ = {width, height};

    // Set parameters from the node item.
    coordinates_ = node_item.coordinates();    

    // Get Icon from the component if any, and update this item once it is
    // downloaded.
    model_item_.component().downloadIcon([this](const auto&) { update(); });
}

NodeLayerItem::~NodeLayerItem() {
}

QRectF NodeLayerItem::rect() const {
    return QRectF(getX() - width() / 2, getY() - height() / 2,
        width(), height());
}

QRectF NodeLayerItem::selectedRect() const {
    return rect().adjusted(-sel_adjustment, -sel_adjustment,
        sel_adjustment, sel_adjustment);
}

QRectF NodeLayerItem::boundingRect() const {
    // We need to add some bounding rectangle adjustments to avoid some
    // circle clipping for selected node.
    return selectedRect().adjusted(-bound_adjustment, -bound_adjustment,
        bound_adjustment, bound_adjustment);
}

QPainterPath NodeLayerItem::shape() const {
    auto path = QPainterPath{};
    path.addEllipse(boundingRect());
    return path;
}

void NodeLayerItem::paint(QPainter* painter, 
    const QStyleOptionGraphicsItem* option, QWidget* /*widget*/) {
    // General layer item setup stuff
    onPaint(painter, option);

    auto rc = rect();    
    
    // Icon
    auto& pixmap = model_item_.component().icon();
    auto source = QRectF(0, 0, pixmap.size().width(), pixmap.size().height());

    auto region = QRegion{rc.toRect(), QRegion::Ellipse};

    painter->save();
    painter->setClipRegion(region);

    painter->drawPixmap(rc, pixmap, source);
    painter->restore();
   
    // Pen
    if (isSelected() || isHighlighted()) {
        auto pen = settings_.pen;
        pen.setColor(settings_.selected_color);
        pen.setWidth(settings_.selected_line_width);
        painter->setPen(pen);
    }

    // Circle
    painter->drawEllipse(rc);

    // Draw a second rectangle for the selected item.
    if (isSelected() || isHighlighted()) {
        auto path = QPainterPath{};

        path.addEllipse(selectedRect());
        path.addEllipse(rect());

        if (isSelected())
            painter->setBrush(Qt::darkCyan);
        else
            painter->setBrush(Qt::darkYellow);

        painter->drawPath(path);        
    }    
}

void NodeLayerItem::setSize(const QSizeF& size) {
    size_ = size;
    update();
}


} // namespace WaterwAIs