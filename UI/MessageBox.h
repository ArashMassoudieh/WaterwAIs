#ifndef MESSAGEBOX_H_8C2504416242F936
#define MESSAGEBOX_H_8C2504416242F936


#include <QMessageBox>
#include <chrono>

namespace WaterwAIs {

using namespace std::chrono_literals;

//////////////////////////////////////////////////////////////////////////
// MessageBox

// This set of "message box" function is supposed to be used in the WaterAIs
// project instead of regular information/question/warning/critical
// functions for showing message boxes.
//
// Regular Qt message box functions hang when running under WebAssembly.


class MessageBox: public QMessageBox {
public:
    explicit MessageBox(QWidget* parent = nullptr);

    MessageBox(Icon icon, const QString& title, const QString& text,
        StandardButtons buttons = NoButton, QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);        

    ~MessageBox() override;

    // Auto close
    void setAutoClose(bool auto_close) { auto_close_ = auto_close; }
    bool autoClose() const { return auto_close_; }

    // Close timeout
    void setCloseTimeout(std::chrono::milliseconds timeout) 
        { close_timeout_ = timeout; }

    std::chrono::milliseconds timeout() const { return close_timeout_; }

    // Show
    static void showMsg(Icon icon, const QString& title, const QString& text,
        StandardButtons buttons = {StandardButton::NoButton},
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    static void information(const QString& title,
        const QString& text, StandardButtons buttons = {StandardButton::Ok},
        QWidget* parent = nullptr) {

        showMsg(Icon::Information, title, text, buttons, parent);
    }

    static void question(const QString& title,
        const QString& text, StandardButtons buttons = {StandardButton::Ok},
        QWidget* parent = nullptr) {

        showMsg(Icon::Question, title, text, buttons, parent);
    }

    static void warning(const QString& title,
        const QString& text, StandardButtons buttons = {StandardButton::Ok},
        QWidget* parent = nullptr) {

        showMsg(Icon::Warning, title, text, buttons, parent);
    }

    static void critical(const QString& title,
        const QString& text, StandardButtons buttons = {StandardButton::Ok},
        QWidget* parent = nullptr) {

        showMsg(Icon::Critical, title, text, buttons, parent);
    }
protected:
    using Clock = std::chrono::steady_clock;

    void showEvent (QShowEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

    std::chrono::milliseconds close_timeout_ = 1500ms;
    bool auto_close_ = true;    
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MESSAGEBOX_H_8C2504416242F936
