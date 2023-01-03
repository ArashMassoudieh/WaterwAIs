
CONFIG += c++14

DEFINES += QT_NO_DEBUG _NO_GSL

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


DEFINES += Arash

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}


# copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # replace slashes in destination path for Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # replace slashes in source path for Windows
        win32:file ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

# Windows
win32: copyToDestDir($$OTHER_FILES, $$OUT_PWD/Json/)

#Linux, others: TBD

wasm {
    QMAKE_LFLAGS += -sASYNCIFY -Os

    # Making WASM to preload Json folder content
    QMAKE_LFLAGS += --preload-file $$PWD/Json
    DEFINES += WASM_PRELOAD_DIR=\"'$$PWD/Json'\"
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



