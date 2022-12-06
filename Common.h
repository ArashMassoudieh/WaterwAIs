#ifndef COMMON_H
#define COMMON_H

#if defined(QT_DEBUG)
#define HOST_PATH "http://localhost:30000"
#define SERVER_PATH "http://192.168.1.2:5004"
#else
#define HOST_PATH "/Users/venkateshputta/WWTP-Project/QMapViewer/Json"
#define SERVER_PATH "http://20.244.11.239/api"
#endif

#endif // COMMON_H
