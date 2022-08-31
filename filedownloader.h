#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    Downloader(const Downloader &downloader);
    Downloader & operator=( const Downloader & );
    void doDownload(const QUrl &url);
    QNetworkReply *Downloaded = nullptr;
signals:

public slots:
    void replyFinished (QNetworkReply *reply);

signals:
    void downloadfinished();

private:
   QNetworkAccessManager *manager;

};

#endif // DOWNLOADER_H
