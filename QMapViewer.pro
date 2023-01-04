
# Enable C++20
CONFIG += c++2a

DEFINES += _NO_GSL

QT += widgets core network

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

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
    about.h \
    dlglayerproperties.h \
    edge.h \
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
    propmodel.h \
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
    about.cpp \
    dlglayerproperties.cpp \
    edge.cpp \
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
    propmodel.cpp \
    segment.cpp \
    variable.cpp \
    variablelist.cpp
SOURCES += mainwindow.cpp

FORMS += \
    dialog.ui \
    dlglayerproperties.ui \
    mapview.ui

RESOURCES += images.qrc

DISTFILES += json/Centroids.geojson \
    json/HickeyRunSewer.geojson \
    json/PourPoints.geojson \
    json/SubWaterSheds.geojson \
    json/1.png \
    json/2.png \
    json/4.png

OTHER_FILES += \
    $$PWD\Json\*.*


#DEFINES += Arash

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

DATA_DIR = $$PWD/Json
DEFINES += DATA_DIR=\"$$DATA_DIR\"

wasm {
    QMAKE_LFLAGS += -sASYNCIFY -Os

    # Direct WASM to load local data files whem starting the app.
    # This is needed to allow to load their content when app
    # is running inside the WASM and use resources from the local
    # data files (JSON, layer icons etc).
    #
    # Production app should load resources from the Cloud and
    # thus not need this
    USE_LOCAL_DATA_FILES = 1

    defined(USE_LOCAL_DATA_FILES, var) {
        message("WASM will preload data files from $$DATA_DIR.")
        # Making WASM to preload Data folder content
        QMAKE_LFLAGS += --preload-file $$DATA_DIR
    }
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



