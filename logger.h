#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

namespace Logger {
    void trace(const QString &msg);
    void debug(const QString &msg);
    void warning(const QString &msg);
    void error(const QString &msg);
}

#endif // LOGGER_H
