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
//#define HOST_PATH "http://localhost/Data"

#define SERVER_PATH "http://20.244.11.239/api"


/////////////////////////////////////////////////////////
#endif // DEFS_H_A4D4292FA26545AF
