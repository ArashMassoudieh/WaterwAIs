#ifndef APPLICATION_H_8A4B1365A0E60012
#define APPLICATION_H_8A4B1365A0E60012

#include <QApplication>

#include <memory>

namespace WaterwAIs {

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

    // Setting host path - base path for names that don't specify absolute path
    static void setHostPath(QStringView path);

    // Returns application URL for WebAssembly run
    static QUrl url();

private:
    // Main Window
    std::unique_ptr<MainWindow> main_window_;

    // Sets settings
    void setSettings();

    static PathSettings paths_;
};

} //namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // APPLICATION_H_8A4B1365A0E60012
