
#include "FeatureModelItem.h"
#include <Layer/SegmentLayerItem.h>
#include <Layer/CircleLayerItem.h>
#include <Layer/PolygonLayerItem.h>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// FeatureModelItem

FeatureModelItem::FeatureModelItem(const FeatureModelItem& C) {
    geometry_ = C.geometry_;
    type_ = C.type_;
}
FeatureModelItem& FeatureModelItem::operator = (const FeatureModelItem& C) {
    geometry_ = C.geometry_;
    type_ = C.type_;
    return *this;
}

FeatureType FeatureModelItem::toType(QStringView type) {
    if (type == u"MultiLineString") return FeatureType::MultiLineString;
    if (type == u"Point"          ) return FeatureType::Point;
    if (type == u"MultiPolygon"   ) return FeatureType::MultiPolygon;
    return FeatureType::Unknown;
}

double FeatureModelItem::getRange(range rng, dir direction) const {
    auto extreme = 0.0;

    if (!geometry_.empty()) {
        auto range_i = (rng == range::max) ? -1 : 1;

        extreme = range_i * 1e12;

        for (auto&& point : geometry_) {
            if (direction == dir::x) {
                if (range_i * point.x() < range_i * extreme)
                    extreme = point.x();
            } else {
                if (range_i * point.y() < range_i * extreme)
                    extreme = point.y();
            }
        }
    }
    return extreme;
}

FeatureModelItem::Ptr FeatureModelItem::create(QStringView type_str) {
    auto type = toType(type_str);

    switch (type) {
    case FeatureType::MultiLineString:
        return std::make_unique<MultiLineStrModelItem>();

    case FeatureType::Point:
        return std::make_unique<PointModelItem>();

    case FeatureType::MultiPolygon:
        return std::make_unique<MultiPolygonModelItem>();
    
    case FeatureType::Unknown:
        break;

    default:
        break;
    }
    return Ptr{};
}


//////////////////////////////////////////////////////////////////////////
// MultiLineStrModelItem

void MultiLineStrModelItem::getFromJson(const QJsonValue& json_value) {
    auto array = json_value.toArray();

    for (auto&& lvl_value : array) {
        auto level1 = lvl_value.toArray();
        for (auto&& coord_value : level1) {
            auto coords = coord_value.toArray();
            geometry_.emplace_back(coords[0].toDouble(), coords[1].toDouble());
        }
    }
}

void MultiLineStrModelItem::addGraphicsItems
    (const LayerGraphicsSettings& gsettings, LayerGraphicsItems& items) {

    for (auto it = geometry_.cbegin(); it != geometry_.cend() - 1; ++it)
        items.addItem(new SegmentLayerItem{gsettings, *it, *(it + 1)});
}


//////////////////////////////////////////////////////////////////////////
// PointModelItem

void PointModelItem::getFromJson(const QJsonValue& json_value) {
    auto array = json_value.toArray();
    geometry_.emplace_back(array[0].toDouble(), array[1].toDouble());
}

void PointModelItem::addGraphicsItems(const LayerGraphicsSettings& gsettings,
    LayerGraphicsItems& items) {

    items.addItem(new CircleLayerItem{gsettings, geometry_.front(), 50});
}


//////////////////////////////////////////////////////////////////////////
// MultiPolygonModelItem

void MultiPolygonModelItem::getFromJson(const QJsonValue& json_value) {
    auto array = json_value.toArray();

    for (auto&& lvl1_value : array) {
        auto level1 = lvl1_value.toArray();

        for (auto&& lvl2_value : level1) {
            auto level2 = lvl2_value.toArray();

            for (auto&& coord_value : level2) {
                auto coords = coord_value.toArray();
                geometry_.emplace_back(coords[0].toDouble(), coords[1].toDouble());
            }
        }
    }
}

void MultiPolygonModelItem::addGraphicsItems
    (const LayerGraphicsSettings& gsettings, LayerGraphicsItems& items) {
    auto plygn = QPolygonF{};

    for (auto&& point : geometry_)
        plygn.append(point);

    items.addItem(new PolygonLayerItem{gsettings, plygn, true});
}

} // namespace WaterwAIs