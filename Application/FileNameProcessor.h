#ifndef FILEPATHPROCESSOR_H_B937935A40D570B5
#define FILEPATHPROCESSOR_H_B937935A40D570B5

#include <QString>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// FilePathProcessor
//
// Abstract class allowing to process file names to obtain ther full paths,
// which can be either local files or URLs.

class FileNameProcessor {
public:
    enum class Hint {
        Host = 0,
        Server
    };

    // Return a full path (local file path or URL) after processing the
    // file name
    virtual QString path(QStringView file_name, Hint hint = Hint::Host) = 0;

    // Returns global file name processor
    static FileNameProcessor& instance();

    // Returns true if file name is URL.
    static bool isUrl(QStringView file_name);
};

// Useful shortcut macros
#define WW_HOST_PATH(x)   FileNameProcessor::instance().path(x, FileNameProcessor::Hint::Host)
#define WW_SERVER_PATH(x) FileNameProcessor::instance().path(x, FileNameProcessor::Hint::Server)

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // FILEPATHPROCESSOR_H_B937935A40D570B5