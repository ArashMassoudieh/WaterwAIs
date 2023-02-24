
# Enable C++20
CONFIG += c++2a

DEFINES += _NO_GSL

QT += widgets core network charts

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

INCLUDEPATH += \
	. \
        Common

FORMS += \
    Forms/chartsettingsdialog.ui \
    Forms/chartwidget.ui \
    Forms/dlglayerproperties.ui \
    Forms/mainview.ui \    
    Forms/itempropertieswidget.ui \
    Forms/panel.ui

HEADERS += \
	Application/Application.h \
	Application/Defs.h \
        Application/FileNameProcessor.h \
        Application/LayersInfo.h \
        Application/TimeSeriesCache.h

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
        MetaModelLayer/GenericItemListModel.h \
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
        UI/Chart/ChartSettingsDlg.h \
        UI/Chart/ChartView.h \
        UI/Chart/ChartWidget.h \
        UI/ItemNavigator.h \
        UI/ItemPropertiesWidget.h \
	UI/LayerPropertiesDialog.h \
	UI/MainView.h \
	UI/MainWindow.h \
	UI/MapScene.h \
        UI/MapView.h \
        UI/MessageBox.h \
        UI/Panel.h


HEADERS += \
        Utilities/TimeSeries_s.h \
        Utilities/TimeSeries_s.hpp \
        Utilities/TimeSeriesSet_s.h \
        Utilities/TimeSeriesSet_s.hpp \
	Utilities/cpoint.h \
        Utilities/Matrix.h \
	Utilities/QuickSort.h \
	Utilities/Utilities.h \
        Utilities/Vector.h

SOURCES += \
	Application/Application.cpp \
        Application/FileNameProcessor.cpp \
        Application/LayersInfo.cpp \
        Application/TimeSeriesCache.cpp

SOURCES += \
	Common/Logger.cpp \
        Common/Downloader.cpp \
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
        MetaModelLayer/GenericItemListModel.cpp \
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
    UI/Chart/ChartSettingsDlg.cpp \
    UI/Chart/ChartView.cpp \
    UI/Chart/ChartWidget.cpp \
    UI/ItemNavigator.cpp \
    UI/ItemPropertiesWidget.cpp \
    UI/LayerPropertiesDialog.cpp \
    UI/MainView.cpp \
    UI/MainWindow.cpp \
    UI/MapScene.cpp \
    UI/MapView.cpp \
    UI/MessageBox.cpp \
    UI/Panel.cpp

SOURCES += \
	Utilities/cpoint.cpp \
	Utilities/Matrix.cpp \
	Utilities/QuickSort.cpp \
	Utilities/Utilities.cpp \
	Utilities/Vector.cpp

SOURCES += main.cpp


RESOURCES += images.qrc


build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

DATA_DIR = $$PWD/Data
DEFINES += DATA_DIR=\"$$DATA_DIR\"

message("DATA_DIR=$$DATA_DIR")

# Specyfying to use local "data" files(models, icons, etc)
# from the project Data folder.
# Production app should load resources from the Cloud and
# thus not need this line.
USE_LOCAL_DATA_FILES = 1

defined(USE_LOCAL_DATA_FILES, var) {
DEFINES += USE_LOCAL_DATA_FILES
}

wasm {
    QMAKE_LFLAGS += -sASYNCIFY -Os

    defined(USE_LOCAL_DATA_FILES, var) {
        # Direct WASM to load local data files whem starting the app.
        # This is needed to allow to load their content when app
        # is running inside the WASM and use resources from the local
        # data files (JSON, layer icons etc).
        #
        # Production app should load resources from the Cloud and
        # thus not need this


        message("WASM will preload data files from $$DATA_DIR")
        # Making WASM to preload Data folder content

        equals(QT_MAJOR_VERSION, 5) {
            # Qt 5.x
            QMAKE_LFLAGS += --preload-file $$DATA_DIR
        }

        greaterThan(QT_MAJOR_VERSION, 5) {
            #Qt 6 and above
            QMAKE_LFLAGS += --preload-file $$DATA_DIR@/
        }
    }
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



