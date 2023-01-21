
#include "Application.h"

#include "UI/MainWindow.h"
#include "FileNameProcessor.h"
#include "Defs.h"

namespace WaterWays {

//////////////////////////////////////////////////////////////////////////
// Application

Application::PathSettings Application::paths_;

Application::Application(int& argc, char** argv, int flags)
    : QApplication{argc, argv, flags} {

    setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    // Setting application settings
    setSettings();

    // Showing main window
    main_window_ = std::make_unique<MainWindow>();

    main_window_->setWindowTitle(APP_NAME);
    main_window_->show();
}

Application::~Application() {
}

void Application::setSettings() {
    // Server path
    paths_.server_path = SERVER_PATH;

    // Host path - Base Url or local folder
    auto url = QUrl{HOST_PATH};
    auto scheme = url.scheme();
    auto is_url = scheme == "http" || scheme == "https";

    paths_.host_path = is_url ? HOST_PATH : "file:" HOST_PATH;
}

} //namespace WaterWays
