#ifndef FEATUREMODELITEM_H_8E087CEE8A46DDBF
#define FEATUREMODELITEM_H_8E087CEE8A46DDBF

#include <Layer/LayerModelItem.h>

#include <QString>
#include <QJsonArray>
#include <QGraphicsItem>

#include "Utilities/cpoint.h"
#include <vector>


namespace WaterwAIs {

class Layer;

enum class FeatureType {
    Unknown = 0,
    MultiLineString,
    Point,
    MultiPolygon,  
};


//////////////////////////////////////////////////////////////////////////
// FeatureModelItem

class FeatureModelItem : public LayerModelItem {
public:
    using GraphicsItems = std::vector<QGraphicsItem*>;
    using Ptr = std::unique_ptr<FeatureModelItem>;

    FeatureModelItem(FeatureType type) : type_{type} {}

    FeatureModelItem(const FeatureModelItem&);
    FeatureModelItem& operator = (const FeatureModelItem& C);

    virtual ~FeatureModelItem() = default;

    FeatureType type() const { return type_; }

    static FeatureType toType(QStringView type);

    void appendToGeometry(const QPoint& pt) {
        geometry_.emplace_back(pt);
    }

    const std::vector<QPoint>& geometry() { return geometry_; }

    double getRange(range rng, dir direction) const;    

    // Creator function
    static Ptr create(QStringView type_str);

protected:
    std::vector<QPoint> geometry_;

private:
    FeatureType type_;
};


//////////////////////////////////////////////////////////////////////////
// MultiLineStrModelItem

class MultiLineStrModelItem: public FeatureModelItem {
public:
    MultiLineStrModelItem(): FeatureModelItem{FeatureType::MultiLineString} {}

    void getFromJson(const QJsonValue& json_value) override;
    void addGraphicsItems(const LayerGraphicsSettings& gsettings,
        LayerGraphicsItems& items) override;
};

//////////////////////////////////////////////////////////////////////////
// PointModelItem

class PointModelItem: public FeatureModelItem {
public:
    PointModelItem(): FeatureModelItem{FeatureType::Point} {}    

    void getFromJson(const QJsonValue& json_value) override;
    void addGraphicsItems(const LayerGraphicsSettings& gsettings,
        LayerGraphicsItems& items) override;
};

//////////////////////////////////////////////////////////////////////////
// MultiPolygonModelItem

class MultiPolygonModelItem: public FeatureModelItem {
public:
    MultiPolygonModelItem(): FeatureModelItem{FeatureType::MultiPolygon} {}

    void getFromJson(const QJsonValue& json_value) override;
    void addGraphicsItems(const LayerGraphicsSettings& gsettings,
        LayerGraphicsItems& items) override;
};

} // namespace WaterwAIs


//////////////////////////////////////////////////////////////////////////
#endif // FEATUREMODELITEM_H_8E087CEE8A46DDBF
