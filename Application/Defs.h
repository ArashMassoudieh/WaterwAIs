#ifndef DEFS_H_A4D4292FA26545AF
#define DEFS_H_A4D4292FA26545AF

#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)

#define APP_NAME "WateraAIs"

//////////////////////////////////////////////////////////////////////////
// Project location-dependent settings
//#define HOST_PATH "/home/arash/Projects/QMapViewer/Json"
//#define HOST_PATH "/Infopact/QMapViewer/Json"

//////////////////////////////////////////////////////////////////////////
// Project location-independent settings
// 

#include <QtGlobal>

#if defined(Q_OS_WASM) && QT_VERSION >= 0x060000 

// In Qt 6.4 Emscripten maps absolute path as a root, so we need to
// ignore whatever DATA_DIR is set and use empty string instead.
#undef DATA_DIR
#endif

// This mechanism uses the DATA_DIR preprocessor definition which is set
// and passed to the compiler during processing the .pro file.

#ifdef DATA_DIR
#define HOST_PATH STRINGIFY(DATA_DIR)
#else
#define HOST_PATH ""
#endif

// Example of loading models and icons from some host server.
//#define SERVER_PATH "http://localhost/Data"
//#define SERVER_PATH "http://20.244.11.239/api"

// NOTE: Empty server path means that the application needs to get the
// server location from the Application::url() call.
#define SERVER_PATH ""

// Force to use server path - if needed for testing etc.
//#undef USE_LOCAL_DATA_FILES

#ifndef USE_LOCAL_DATA_FILES
#undef HOST_PATH
#define HOST_PATH SERVER_PATH
#endif // !USE_LOCAL_DATA_FILES


/////////////////////////////////////////////////////////


// Name of the file containing layers information
// #define LAYERS_FILE u"Layers_example.json"
// #define LAYERS_FILE u"Layers_example_lhost.json"

//#define LAYERS_FILE u"Layers_sligo.json"

#define LAYERS_FILE u"Layers.json"

// Specifies that application should load only model layer
//#define IGNORE_FEATURE_LAYERS

/////////////////////////////////////////////////////////
#endif // DEFS_H_A4D4292FA26545AF
