#include "translator.h"
#include <QFile>

Translator::Translator(QObject *parent) : QObject(parent)
{
    ReadDirectoryInfo();
    connect(&timer, SIGNAL(timeout()),this, SLOT(translate()));
    timer.start(readInterval*1000);
}

bool Translator::ReadDirectoryInfo()
{
    QFile file;
    file.setFileName("../Data/TimeSeriesTranslatorConfig.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return false;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return false;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();
    OHQFilePath = jsonObj["MainOHQoutput"].toString();
    OutputFolder = jsonObj["TimeSeriesFolder"].toString();
    readInterval = jsonObj["ReadInterval"].toInt();
    return true;

}

void Translator::translate()
{
    qDebug()<<"Translating ...";
    CTimeSeriesSet<double> mainoutput(OHQFilePath.toStdString(),true);
    for (int i=0; i<mainoutput.nvars; i++)
    {
        mainoutput[i].writefile(OutputFolder.toStdString() + "/" + mainoutput.names[i]+".csv");
    }
}
