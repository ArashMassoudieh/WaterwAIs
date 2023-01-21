#ifndef DOWNLOADER_H_BEFAEB97C825D5AD
#define DOWNLOADER_H_BEFAEB97C825D5AD

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QPixmap>

namespace WaterWays {

template <typename T>
inline T download_to(const QByteArray& data);

template <>
inline QByteArray download_to(const QByteArray& data) { return data; }

//////////////////////////////////////////////////////////////////////////
// Downloader
//
// Class allowing to perform asynchronous downloading operations
// It calls user callback when download is finished (even with error)
// and provides downloaded data in case of success.
// 
// It provides ability to convert downloaded data to some end types like
// QString or QJsonDocument or QPixmap
//
// A typical use is like:
// auto downloader = Downloader{};
//
// downloader.download<QPixmap>
//      (path, [](auto result, const auto& image)) {
//         Do something with the downloaded image
//         if result is true
// }
// 
// 

class Downloader: public QObject {
    Q_OBJECT
public:
    template <typename T>
    using DownloadCallback = std::function<void(bool, T&&)>;

    void downloadData(const QUrl& url, DownloadCallback<QByteArray> callback) {
        if (!callback) {
            qDebug() << "Url:" << url << ", empty download callback was"
                " specified";
            return;
        }

        auto reply = netrwork_mgr_.get(QNetworkRequest(url));

        connect(reply, &QNetworkReply::finished, this, [this, reply, callback]() {
            if (reply->error()) {
                // Our download finished with error, so we can't proceed
                qDebug() << "Url:" << reply->url() << ", Error occurred: "
                    << reply->errorString();

                callback(false, {});
            } else {
                auto data = reply->readAll();
                //qDebug() << reply->header(QNetworkRequest::KnownHeaders{});

                callback(true, std::move(data));
            }
            reply->deleteLater();
        });
    }

    template <typename T>
    void download(const QUrl& url, DownloadCallback<T> callback) {
        if (!callback) {
            qDebug() << "Url:" << url << ", empty download callback was"
                " specified";
            return;
        }
        downloadData(url, [callback](auto result, const auto& data) {
            callback(result, download_to<T>(data));
            });
    }

    template <typename T, typename U>
    void download(U path, DownloadCallback<T> callback) {
        download<T>(QUrl{QString{path}}, callback);
    }

private:
    QNetworkAccessManager netrwork_mgr_;
};


// Download conversion functions
template <>
inline QJsonDocument download_to(const QByteArray& data) {
    return QJsonDocument().fromJson(data);
}

template <>
inline QString download_to(const QByteArray& data) {
    return QString{data};
}

template <>
inline QPixmap download_to(const QByteArray& data) {
    auto pixmap = QPixmap{};
    pixmap.loadFromData(data);
    return pixmap;
}

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // DOWNLOADER_H_BEFAEB97C825D5AD