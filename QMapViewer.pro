RESOURCES += images.qrc

INCLUDEPATH += ../Utilities

HEADERS += mainwindow.h \
    ../Utilities/BTC.h \
    ../Utilities/BTC.hpp \
    ../Utilities/BTCSet.h \
    ../Utilities/BTCSet.hpp \
    ../Utilities/Matrix.h \
    ../Utilities/QuickSort.h \
    ../Utilities/Utilities.h \
    ../Utilities/Vector.h \
    ../Utilities/cpoint.h \
    Circle.h \
    feature.h \
    filedownloader.h \
    graphicsitem.h \
    graphicsitemcollection.h \
    graphicsview.h \
    layer.h \
    logger.h \
    mapscene.h \
    mapview.h \
    polygon.h \
    segment.h \
    variable.h \
    variablelist.h
SOURCES += main.cpp \
    ../Utilities/Matrix.cpp \
    ../Utilities/QuickSort.cpp \
    ../Utilities/Utilities.cpp \
    ../Utilities/Vector.cpp \
    ../Utilities/cpoint.cpp \
    Circle.cpp \
    feature.cpp \
    filedownloader.cpp \
    graphicsitem.cpp \
    graphicsitemcollection.cpp \
    graphicsview.cpp \
    layer.cpp \
    logger.cpp \
    mapscene.cpp \
    mapview.cpp \
    polygon.cpp \
    segment.cpp \
    variable.cpp \
    variablelist.cpp
SOURCES += mainwindow.cpp

QT += widgets core network

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/chip
INSTALLS += target

DISTFILES +=

FORMS += \
    mapview.ui

