#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include "TimeSeriesSet_s.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QTimer"

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = nullptr);
    bool ReadDirectoryInfo();

private:
    QString OHQFilePath;
    QString OutputFolder;
    int readInterval = 300; //reading time interval in seconds
    QTimer timer;
signals:

public slots:
    void translate();

};

#endif // TRANSLATOR_H
