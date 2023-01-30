
#include "MetaComponentItem.h"
#include <Application/FileNameProcessor.h>
#include <Downloader.h>


namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// IconDownoader

class MetaComponentItem::IconDownloader {
public:
    IconDownloader(MetaComponentItem& item): 
        downloader_{new Downloader{}, downloaderDeleter}, item_{item} {}

    void downloadIcon(IconDownloadedFunc callback) {
        item_.icon_ = QPixmap{};
        addObserver(callback);

        downloader_->download<QPixmap>(WW_HOST_PATH(item_.iconPath()),
            [this] (auto result, const auto& image) {
                if (result) {
                    item_.icon_ = image;
                    qDebug() << "MetaItem, icon: " << item_.iconPath() <<
                        "successfully downloaded";
                }

                // Notify all observers that the icon was downloaded        
                for (auto& observer : callbacks_)
                    observer(item_.icon_);

                // Release the downloader as we don't need it anymore.
                item_.icon_downloader_.reset();
            });
    }

    void addObserver(IconDownloadedFunc callback)
        { callbacks_.emplace_back(callback); }

private:    
    static void downloaderDeleter(Downloader* p) { p->deleteLater(); }

    std::unique_ptr <Downloader, void(*)(Downloader*)> downloader_;
    MetaComponentItem&   item_;

    std::vector<IconDownloadedFunc> callbacks_;
};


//////////////////////////////////////////////////////////////////////////
// MetaComponentItem

MetaComponentItem::~MetaComponentItem() = default;

MetaComponentItem::MetaComponentItem(const QJsonObject& json_object)
    : type_ {Type::Unknown} {
    for(auto& key: json_object.keys()) {
        if (key == "icon")
            icon_path_ = json_object.value(key).toString();
        else if (key == "type") {
            if (json_object.value(key).toString() == "node")
                type_ = Type::Node;
                
            if (json_object.value(key).toString() == "link")
                type_ = Type::Link;
        } else {
            // Specifies a property, so let's store it
            properties_.set(key, json_object.value(key).toObject());
        }
    }
}

void MetaComponentItem::setIconPath(QStringView icon_path) {
    icon_path_ = icon_path.toString();
    icon_ = QPixmap{};
    icon_downloader_.reset();
}

void MetaComponentItem::downloadIcon(IconDownloadedFunc callback) {
    if (!icon_.isNull()) {
        // Icon is already downloaded.
        callback(icon_);
        return;
    }

    if (icon_downloader_) {
        // Icon download is already in progress.
        icon_downloader_->addObserver(callback);
        return; 
    }    
    
    if (icon_path_.isEmpty()) {
        // Icon path was not specified.
        callback(icon_);
        return;
    }

    // Start icon download
    icon_downloader_ = std::make_unique<IconDownloader>(*this);
    icon_downloader_->downloadIcon(callback);
}

QString MetaComponentItem::typeToSting(Type type) {
    switch (type) {    
        case Type::Node  : return "Node";
        case Type::Link  : return "Link";        
        case Type::Entity: return "Entity";        
        default: break;
    }
    return "Unknown";
}


} // namespace WaterwAIs