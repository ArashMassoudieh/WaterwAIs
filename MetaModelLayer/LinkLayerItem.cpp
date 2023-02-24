
#include "LinkLayerItem.h"
#include "NodeLayerItem.h"
#include <cmath>

#include <QVector2D>

namespace WaterwAIs {

namespace {    
    static constexpr auto link_arrow_size = 10.0;    
    static constexpr auto link_line_width = 7;

    static constexpr double Pi = 3.14159265358979323846264338327950288419717;
    static constexpr double TwoPi = 2.0 * Pi;

} // anonymous


//////////////////////////////////////////////////////////////////////////
// LinkLayerItem

LinkLayerItem::LinkLayerItem(const LayerGraphicsSettings& gsettings,
    LinkItem& link_item, const NodeLayerItem* src_node,
    const NodeLayerItem* dest_node)
    : MetaLayerItem{gsettings, link_item}
    , source_node_{src_node}, dest_node_{dest_node}
    , arrow_size_{link_arrow_size} {

    adjust();
}

QRectF LinkLayerItem::boundingRect() const {
    if (!source_node_ || !dest_node_)
        return QRectF{};
    
    auto extra = (link_line_width + 2 * arrow_size_);

    auto rect = QRectF{
        source_point_, 
        QSizeF{dest_point_.x() - source_point_.x(),
               dest_point_.y() - source_point_.y()}}
    .normalized().adjusted(-extra, -extra, extra, extra);

    return rect;
}

void LinkLayerItem::paint(QPainter* painter, 
    const QStyleOptionGraphicsItem* option, QWidget* /*widget*/) {
    if (!source_node_ || !dest_node_)
        return;
    
    // General layer item setup stuff
    onPaint(painter, option);
    
    auto line = QLineF{source_point_, dest_point_};
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;    

    // Use layer's color
    auto color = settings_.pen.color();
    auto line_width = static_cast<qreal>(link_line_width);
    auto arrow_size = arrow_size_;

    // Draw the line itself
    if (isSelected()) {
        color = settings_.selected_color;
        
        line_width *= 2;
        arrow_size *= 2;
    }

    auto pen = QPen{color, line_width, Qt::SolidLine, Qt::RoundCap,
        Qt::RoundJoin};

    painter->setPen(pen);
    painter->drawLine(line);    

    // Draw the arrows
    painter->setBrush(color);
    
    auto angle = ::acos(line.dx() / line.length());

    if (line.dy() >= 0)
        angle = TwoPi - angle;

    auto dest_arrow_p1 = dest_point_ +
        QPointF{sin(angle - Pi / 3) * arrow_size,
                cos(angle - Pi / 3) * arrow_size};

    auto dest_arrow_p2 = dest_point_ +
        QPointF{sin(angle - Pi + Pi / 3) * arrow_size,
                cos(angle - Pi + Pi / 3) * arrow_size};

    painter->drawPolygon(QPolygonF{} << line.p2() <<
        dest_arrow_p1 << dest_arrow_p2);
}


void LinkLayerItem::adjust() {
    if (!source_node_ || !dest_node_)
        return;

    auto line = QLineF{source_node_->origin(), dest_node_->origin()};

    prepareGeometryChange();

    auto vect = QVector2D{};
    vect.setX(line.p2().x() - line.p1().x());
    vect.setY(line.p2().y() - line.p1().y());
    double length = vect.length();


    auto edge_offset_source = QPointF{vect.x() / length * source_node_->width() / 2,
                                      vect.y() / length * source_node_->width() / 2};

    auto edge_offset_dest = QPointF{vect.x() / length * dest_node_->width() / 2,
                                    vect.y() / length * dest_node_->width() / 2};

    source_point_ = line.p1() + edge_offset_source;
    dest_point_   = line.p2() - edge_offset_dest;
}


QPainterPath LinkLayerItem::shape() const {
    auto path = QPainterPath{};

    auto line = QLineF{source_point_, dest_point_};

    if (qFuzzyCompare(line.length(), qreal(0.))) {
        path.addRect(boundingRect());
        return path;
    }

    auto polygon = QPolygonF{};

    if (std::abs(line.dx()) > std::abs(line.dy())) {
        auto half_height = link_line_width + arrow_size_;

        // Points 1 and 2
        polygon.append({source_point_.x(), source_point_.y() - half_height});
        polygon.append({source_point_.x(), source_point_.y() + half_height});

        // Points 3 and 4
        polygon.append({dest_point_.x(), dest_point_.y() + half_height});
        polygon.append({dest_point_.x(), dest_point_.y() - half_height});

        // Point 5 = point 1
        polygon.append({source_point_.x(), source_point_.y() - half_height});
    } else {
        auto half_width = link_line_width + arrow_size_;

        // Points 1 and 2
        polygon.append({source_point_.x() - half_width, source_point_.y()});
        polygon.append({source_point_.x() + half_width, source_point_.y()});

        // Points 3 and 4
        polygon.append({dest_point_.x() + half_width, dest_point_.y()});
        polygon.append({dest_point_.x() - half_width, dest_point_.y()});

        // Point 5 = point 1
        polygon.append({source_point_.x() - half_width, source_point_.y()});
    }

    path.addPolygon(polygon);
    return path;
}


} // namespace WaterwAIs
