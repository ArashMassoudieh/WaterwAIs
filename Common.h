#ifndef COMMON_H
#define COMMON_H

#if defined(QT_DEBUG)
#define HOST_PATH "http://localhost:30000"
#define SERVER_PATH "http://192.168.1.2:5004"
#else
#ifndef Arash
//#define HOST_PATH "http://20.244.11.239/json"
//#else
#define HOST_PATH "/Users/venkateshputta/WWTP-Project/QMapViewer/Json"
#else
//#define HOST_PATH "/home/arash/Projects/QMapViewer/Json"
//#define HOST_PATH "/Infopact/QMapViewer/Json"

// User-independent settings
#ifndef Q_OS_WASM
    #define HOST_PATH "Json"
#else
#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)

    #define HOST_PATH STRINGIFY(WASM_PRELOAD_DIR)
#endif

#endif
#define SERVER_PATH "http://20.244.11.239/api"
#endif

#endif // COMMON_H
