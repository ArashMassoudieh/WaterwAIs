#include <QCoreApplication>
#include <QTimer>
#include "translator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Translator translator;

    return a.exec();
}
