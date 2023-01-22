
# Enable C++20
CONFIG += c++2a

DEFINES += _NO_GSL WASM

#KIT = Desktop
KIT = WASM

QT += widgets core network

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

contains( KIT, Desktop ) {
     QMAKE_CXXFLAGS += -fconcepts
     DEFINES += Desktop_version
}

INCLUDEPATH += \
	. \
        Common

FORMS += \
    Forms/dlglayerproperties.ui \
    Forms/mainview.ui

HEADERS += \
	Application/Application.h \
	Application/Defs.h \
	Application/FileNameProcessor.h \

HEADERS += \
	Common/Layer/CircleLayerItem.h \
	Common/Layer/Layer.h \
	Common/Layer/LayerGraphicsItem.h \
	Common/Layer/LayerItemDelegate.h \
	Common/Layer/LayerListModel.h \
	Common/Layer/LayerModel.h \
	Common/Layer/LayerModelItem.h \
	Common/Layer/LayerSceneInterface.h \
	Common/Layer/PolygonLayerItem.h \
	Common/Layer/SegmentLayerItem.h \
	Common/Downloader.h \
	Common/Logger.h \
	Common/qstr_unordered_map.h
	
HEADERS += \
	FeatureLayer/FeatureLayer.h \
	FeatureLayer/FeatureModelItem.h

HEADERS += \
	MetaModelLayer/LinkLayerItem.h \
	MetaModelLayer/MetaComponentItem.h \
	MetaModelLayer/MetaItemPropertyModel.h \
	MetaModelLayer/MetaLayerItem.h \
	MetaModelLayer/MetaLayerModel.h \
	MetaModelLayer/MetaLayerModelItem.h \
	MetaModelLayer/MetaModelLayer.h \
	MetaModelLayer/NodeLayerItem.h \
	MetaModelLayer/Variable.h

HEADERS += \
	UI/LayerPropertiesDialog.h \
	UI/MainView.h \
	UI/MainWindow.h \
	UI/MapScene.h \
	UI/MapView.h \

HEADERS += \
	Utilities/_BTC.h \
	Utilities/_BTCSet.h \
	Utilities/BTC.h \
	Utilities/cpoint.h \
	Utilities/Matrix.h \
	Utilities/NormalDist.h \
	Utilities/QuickSort.h \
	Utilities/Utilities.h \
	Utilities/Vector.h \	
	Utilities/BTC.hpp \
	Utilities/BTCSet.hpp

SOURCES += \
	Application/Application.cpp \
	Application/FileNameProcessor.cpp \


SOURCES += \
	Common/Logger.cpp \
	Common/Layer/CircleLayerItem.cpp \
	Common/Layer/Layer.cpp \
	Common/Layer/LayerItemDelegate.cpp \
	Common/Layer/LayerListModel.cpp \
	Common/Layer/LayerModel.cpp \
	Common/Layer/PolygonLayerItem.cpp \
	Common/Layer/SegmentLayerItem.cpp

SOURCES += \
	FeatureLayer/FeatureLayer.cpp \
	FeatureLayer/FeatureModelItem.cpp

SOURCES += \
	MetaModelLayer/LinkLayerItem.cpp \
	MetaModelLayer/MetaComponentItem.cpp \
	MetaModelLayer/MetaItemPropertyModel.cpp \
	MetaModelLayer/MetaLayerItem.cpp \
	MetaModelLayer/MetaLayerModel.cpp \
	MetaModelLayer/MetaLayerModelItem.cpp \
	MetaModelLayer/MetaModelLayer.cpp \
	MetaModelLayer/NodeLayerItem.cpp \
	MetaModelLayer/Variable.cpp
	
SOURCES += \
    UI/LayerPropertiesDialog.cpp \
    UI/MainView.cpp \
    UI/MainWindow.cpp \
    UI/MapScene.cpp \
    UI/MapView.cpp

SOURCES += \
	Utilities/cpoint.cpp \
	Utilities/Matrix.cpp \
	Utilities/QuickSort.cpp \
	Utilities/Utilities.cpp \
	Utilities/Vector.cpp

SOURCES += main.cpp


RESOURCES += images.qrc

DISTFILES += json/Centroids.geojson \
    json/HickeyRunSewer.geojson \
    json/PourPoints.geojson \
    json/SubWaterSheds.geojson \
    json/1.png \
    json/2.png \
    json/3.png \
    json/4.png \
    json/5.png

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



