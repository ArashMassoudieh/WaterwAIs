#ifndef COMMON_H
#define COMMON_H

// The code block below will be used only for Qt debug builds.
//#if defined(QT_DEBUG)
//#define HOST_PATH "http://localhost:30000"
//#define SERVER_PATH "http://192.168.1.2:5004"
//#else
//#endif

#ifdef Arash
    //#define HOST_PATH "http://20.244.11.239/json"
    #define HOST_PATH "/home/arash/Projects/QMapViewer/Json"
#else
    // Project location-dependent settings
    //#define HOST_PATH "/home/arash/Projects/QMapViewer/Json"
    //#define HOST_PATH "/Infopact/QMapViewer/Json"

    // Project location-independent settings
    // This mechanism uses the DATA_DIR preprocessor definition which is set
    // and passed to the compiler during processing the .pro file.
    #define _STR(x) #x
    #define STRINGIFY(x)  _STR(x)

    #define HOST_PATH STRINGIFY(DATA_DIR)

    #define SERVER_PATH "http://20.244.11.239/api"
#endif

/////////////////////////////////////////////////////////
#endif // COMMON_H
