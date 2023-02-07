
#include "LayerModel.h"
#include <Application/FileNameProcessor.h>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// LayerModel

void LayerModel::clear() {
    items_.clear();
    onClear();
}

void LayerModel::getFromJson(QStringView json_file) {
    model_downloaded_ = false;

    downloadJson(WW_HOST_PATH(json_file),
        [this](auto result, auto&& json_doc) {
            clear();
            if(result) {
                model_downloaded_ = true;
                onModelDownloaded(std::move(json_doc));
            } else {
                qDebug() << "Layer model loading failed";
                return;
            }
        });
}

void LayerModel::onModelDownloaded(QJsonDocument&& json_doc) {
    // By default, we just build the model from the JSON doc and emit
    // modelLoaded() signal.
    // 
    // Derived classes may want to do more complicated things before signaling
    // that model is ready.
    getFromJsonDocument(json_doc);

    emit modelLoaded();
}

void LayerModel::addGraphicsItems(const LayerGraphicsSettings& gsettings,
    LayerGraphicsItems& items) {
    // Adding graphics items from all model items.
    for (auto& item : items_)
        item->addGraphicsItems(gsettings, items);
}

void LayerModel::downloadJson(QStringView json_file,
    JsonDownloadedFunc callback) {
    Downloader::instance().
        download<QJsonDocument>(json_file.toString(), callback);
}

void LayerModel::getIcon(QStringView icon_path, QSize icon_size) {
    Downloader::instance().download<QPixmap>(WW_HOST_PATH(icon_path),
        [icon_size = std::move(icon_size), this]
            (auto result, const auto& image) {

            if (result) {
                // Store scaled image according to the size if it is specified.
                icon_ = icon_size.isEmpty() ? image : image.scaled(icon_size);
                emit iconLoaded();
            }
    });
}

} // namespace WaterwAIs