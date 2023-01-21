
#include "FileNameProcessor.h"
#include "Application.h"
#include <QDebug>

namespace WaterWays {

class FileNameProcessorImpl: public FileNameProcessor {
public:
    QString path(QStringView file_name, Hint hint = Hint::Host) override {
        auto& paths = Application::paths();

        auto file_path = hint == Hint::Host ? paths.host_path
            : paths.server_path;

        if (file_name.isEmpty())
            return file_path;        

        auto name = file_name.toString();

        file_path = file_name.startsWith('/') ? file_path + name
            : file_path + QChar('/') + name;

        qDebug() << "file_path" << file_path;

        return file_path;
    }
};

FileNameProcessor& FileNameProcessor::get() {
    static auto fn_processor = FileNameProcessorImpl{};
    return fn_processor;
}


} // namespace WaterWays