
#include "Application.h"

#include "UI/MainWindow.h"
#include "FileNameProcessor.h"
#include "Defs.h"

#ifndef Q_OS_WASM
#include <QScreen>
#endif // Q_OS_WASM

#ifdef EMSCRIPTEN
#include <emscripten/val.h>
#include <emscripten.h>
#endif


#include <QDebug>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// Application

Application::PathSettings Application::paths_;

Application::Application(int& argc, char** argv, int flags)
    : QApplication{argc, argv, flags} {

    setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    setAttribute(Qt::AA_EnableHighDpiScaling);
    setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Setting application settings
    setSettings();

    // Showing main window
    main_window_ = std::make_unique<MainWindow>();

    main_window_->setWindowTitle(APP_NAME);    

#ifndef Q_OS_WASM
    // Making the initial application size for the desktop mode ~half of the
    // screen.
    auto screen = primaryScreen();
    auto screen_geometry = screen->geometry();

    int height = 1 * screen_geometry.height() / 2;
    int width  = 1 * screen_geometry.width()  / 2;

    main_window_->resize(width, height);
#endif // Q_OS_WASM

    qDebug() << "Apps url: " << Application::url();

    main_window_->show();

}

Application::~Application() {
}

void Application::setSettings() {
    // Server path
    paths_.server_path = SERVER_PATH;

    // Host path - Base Url or local folder
    auto host_path = QStringLiteral(HOST_PATH);

    if (host_path.isEmpty()) {
        // Special case when host path is empty. In this case, we should try
        // to get host path from the application Url, if any.

        if (auto app_url = url(); !app_url.isEmpty()) {
            host_path = app_url.adjusted(QUrl::RemoveFilename).toString()
                + "Data";
        }
    }
    setHostPath(host_path);
}

void Application::setHostPath(QStringView path) {    
    auto is_url = FileNameProcessor::isUrl(path);
    auto host_path = path.toString();

    paths_.host_path = is_url ? host_path : "file:" + host_path;
}


QUrl Application::url() {
#ifdef EMSCRIPTEN
    emscripten::val location = emscripten::val::global("location");
    return QUrl(QString::fromStdString(location["href"].as<std::string>()));
#else
    return QUrl("http://localhost:30000/WateraAIs.html");
#endif
}


} //namespace WaterwAIs
