#ifndef APPLICATION_H_8A4B1365A0E60012
#define APPLICATION_H_8A4B1365A0E60012

#include <QApplication>

namespace WaterWays {

class MainWindow;

//////////////////////////////////////////////////////////////////////////
// Application
//
// Main application class

class Application: public QApplication {
public:
    Application(int& argc, char** argv, int flags = ApplicationFlags);
    ~Application() override;

    struct PathSettings {
        QString host_path;
        QString server_path;
    };

    // Return path settings
    static const PathSettings& paths() { return paths_; }

private:
    // Main Window
    std::unique_ptr<MainWindow> main_window_;

    // Sets settings
    void setSettings();

    static PathSettings paths_;
};

} //namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif // APPLICATION_H_8A4B1365A0E60012