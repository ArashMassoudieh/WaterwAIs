#ifndef DEFS_H_A4D4292FA26545AF
#define DEFS_H_A4D4292FA26545AF

#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)

#define APP_NAME "WaterWays"

//////////////////////////////////////////////////////////////////////////
// Project location-dependent settings
//#define HOST_PATH "/home/arash/Projects/QMapViewer/Json"
//#define HOST_PATH "/Infopact/QMapViewer/Json"

//////////////////////////////////////////////////////////////////////////
// Project location-independent settings
// This mechanism uses the DATA_DIR preprocessor definition which is set
// and passed to the compiler during processing the .pro file.

#define HOST_PATH STRINGIFY(DATA_DIR)

// Example of loading models and icons from some host server.
//#define HOST_PATH "http://localhost/Data"

#define SERVER_PATH "http://20.244.11.239/api"


/////////////////////////////////////////////////////////
#endif // DEFS_H_A4D4292FA26545AF
