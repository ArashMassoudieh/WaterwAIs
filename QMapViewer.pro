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
    Common.h \
    dlglayerproperties.h \
    feature.h \
    filedownloader.h \
    graphicsitem.h \
    graphicsitemcollection.h \
    graphicsview.h \
    layer.h \
    layeritemdelegate.h \
    layeritemmodel.h \
    logger.h \
    mapscene.h \
    mapview.h \
    metamodel.h \
    modellayer.h \
    node.h \
    object.h \
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
    dlglayerproperties.cpp \
    feature.cpp \
    filedownloader.cpp \
    graphicsitem.cpp \
    graphicsitemcollection.cpp \
    graphicsview.cpp \
    layer.cpp \
    layeritemdelegate.cpp \
    layeritemmodel.cpp \
    logger.cpp \
    mapscene.cpp \
    mapview.cpp \
    metamodel.cpp \
    modellayer.cpp \
    node.cpp \
    object.cpp \
    polygon.cpp \
    segment.cpp \
    variable.cpp \
    variablelist.cpp
SOURCES += mainwindow.cpp

DEFINES += QT_NO_DEBUG _NO_GSL

QT += widgets core network

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

wasm {
    QMAKE_LFLAGS += -sASYNCIFY -Os
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/chip
INSTALLS += target

DISTFILES += json/Centroids.geojson \
    json/HickeyRunSewer.geojson \
    json/PourPoints.geojson \
    json/SubWaterSheds.geojson \
    json/1.png \
    json/2.png \
    json/3.png \
    json/4.png

FORMS += \
    dlglayerproperties.ui \
    mapview.ui

