
#include "Application.h"

#include "UI/MainWindow.h"
#include "FileNameProcessor.h"
#include "Defs.h"

#ifndef Q_OS_WASM
#include <QScreen>
#endif // Q_OS_WASM

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

    main_window_->show();

}

Application::~Application() {
}

void Application::setSettings() {
    // Server path
    paths_.server_path = SERVER_PATH;

    // Host path - Base Url or local folder
    setHostPath(QStringLiteral(HOST_PATH));
}

void Application::setHostPath(QStringView path) {    
    auto is_url = FileNameProcessor::isUrl(path);
    auto host_path = path.toString();

    paths_.host_path = is_url ? host_path : "file:" + host_path;
}

} //namespace WaterwAIs
