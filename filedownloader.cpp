#include "filedownloader.h"

Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
}

Downloader::Downloader(const Downloader &downloader)
{

}

Downloader & Downloader::operator=( const Downloader &downloader)
{
    return *this;
}

void Downloader::doDownload(const QUrl &url)
{
    qDebug()<< "Trying to access the file...";

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(url));
}

void Downloader::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "Error Happend!";
        qDebug() << "1) " << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << "2) " << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << "3) " << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << "4) " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "5) " << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        Downloaded = reply;
        emit downloadfinished();
    }

}
