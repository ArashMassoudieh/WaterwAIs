#include <QDebug>
#include "logger.h"

void Logger::trace(const QString &msg)
{
    qDebug() << "TRACE:" << msg;
}

void Logger::debug(const QString &msg)
{
    qDebug() << "DEBUG:" << msg;
}

void Logger::warning(const QString &msg)
{
    qDebug() << "WARN:" << msg;
}

void Logger::error(const QString &msg)
{
    qDebug() << "ERROR:" << msg;
}

