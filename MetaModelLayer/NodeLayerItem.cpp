
#include "NodeLayerItem.h"

namespace WaterWays {

namespace {
    // Default Node parameters    
    static constexpr double node_width    = 200;
    static constexpr double node_height   = 200;    
} // anonymous

//////////////////////////////////////////////////////////////////////////
// NodeLayerItem

NodeLayerItem::NodeLayerItem(const LayerGraphicsSettings& gsettings,
    NodeItem& node_item)
    : MetaLayerItem{gsettings, node_item} {

    // Size
    size_ = {node_width, node_height};

    // Set parameters from the node item.
    coordinates_ = node_item.coordinates();    

    // Get Icon from the component if any, and update this item once it is
    // downloaded.
    model_item_.component().downloadIcon([this](const auto&) { update(); });
}

NodeLayerItem::~NodeLayerItem() {
}

QRectF NodeLayerItem::boundingRect() const {
    return QRectF(getX()-width() / 2, getY()-height() / 2,
        width(), height());
}

QPainterPath NodeLayerItem::shape() const {
    auto path = QPainterPath{};
    path.addRect(boundingRect());
    return path;
}

void NodeLayerItem::paint(QPainter* painter, 
    const QStyleOptionGraphicsItem* option, QWidget* /*widget*/) {
    // General layer item setup stuff
    onPaint(painter, option);

    auto& pixmap = model_item_.component().icon();
   
    /* ???
    auto iconmargin = 0.0;

    auto rect = QRectF{
        boundingRect().left() * 0 + iconmargin * boundingRect().width(),
        boundingRect().top()  * 0 + iconmargin * boundingRect().width(),
        boundingRect().width()  * (1 - iconmargin),
        boundingRect().height() * (1 - iconmargin)};
    */

    // Icon
    auto source = QRectF(0, 0, pixmap.size().width(), pixmap.size().height());
    painter->drawPixmap(boundingRect(), pixmap, source);

    // Circle
    painter->drawEllipse(boundingRect());
}

void NodeLayerItem::setSize(const QSizeF& size) {
    size_ = size;
    update();
}


} // namespace WaterWays