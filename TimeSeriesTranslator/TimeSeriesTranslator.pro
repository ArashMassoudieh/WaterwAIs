QT -= gui

CONFIG += c++2a console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
        . \
        ../Common \
        ../Utilities

SOURCES += \
        ../Utilities/Utilities.cpp \
        main.cpp \
        translator.cpp



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../Utilities/TimeSeriesSet_s.h \
    ../Utilities/TimeSeriesSet_s.hpp \
    ../Utilities/TimeSeries_s.h \
    ../Utilities/TimeSeries_s.hpp \
    translator.h
