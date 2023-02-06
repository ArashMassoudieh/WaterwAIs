#ifndef LAYERMODEL_H_A7E44A83E2B95592
#define LAYERMODEL_H_A7E44A83E2B95592

#include "LayerModelItem.h"
#include <Common/Downloader.h>
#include <deque>

namespace WaterwAIs {


//////////////////////////////////////////////////////////////////////////
// LayerModel

class LayerModel: public QObject {
    Q_OBJECT
public:
    using GraphicsItems = LayerModelItem::GraphicsItems;

    // Default icon size for presentation in layer list model.
    static constexpr auto default_icon_size = QSize{24, 24};

    // Clears the model
    void clear();

    // Builds model from JSON Url and adds it to the scene.
    void getFromJson(QStringView json_file);

    // Allows to provide graphics items from model items to the presentation
    // layer
    void addGraphicsItems(const LayerGraphicsSettings& gsettings,
        LayerGraphicsItems& items);

    // Name
    QString name() const { return name_; }
    void setName(QStringView val) { name_ = val.toString(); }

    // Icon
    void getIcon(QStringView icon_path, QSize icon_size = default_icon_size);
    const QPixmap& icon() const { return icon_; }

signals:
    void modelLoaded();
    void iconLoaded();

protected:
    using JsonDownloadedFunc = Downloader::DownloadCallback<QJsonDocument>;

    // Asynchronously downloads JSON file from 'json_file', which is converted
    // to the full path.
    void downloadJson(QStringView json_file, JsonDownloadedFunc callback);

    // Fills the model from some JSON document    
    virtual void getFromJsonDocument(const QJsonDocument& json_doc) = 0;

    // Notification about clearing the model allowing derived classes to
    // perform their specific clearing actions.
    virtual void onClear() {}

    // Notification that model has been downloaded.
    virtual void onModelDownloaded(QJsonDocument&& json_doc);

    // Item key/value container, where key is item name
    std::deque<std::unique_ptr<LayerModelItem>> items_;

    bool model_downloaded_ = false;

private:
    QString name_;

    // Layer icon
    QPixmap icon_;    
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif //LAYERMODEL_H_A7E44A83E2B95592
