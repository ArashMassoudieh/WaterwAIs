#ifndef MESSAGEBOX_H_8C2504416242F936
#define MESSAGEBOX_H_8C2504416242F936

#include <QMessageBox>

namespace WaterwAIs {
namespace MessageBox {

using Icon = QMessageBox::Icon;
using StandardButton  = QMessageBox::StandardButton;
using StandardButtons = QMessageBox::StandardButtons;

//////////////////////////////////////////////////////////////////////////
// MessageBox

// This set of "message box" function is supposed to be used in the WaterAIs
// project instead of regular information/question/warning/critical
// functions for showing message boxes.
//
// Regular Qt message box functions hang when running under WebAssembly.

inline void show(Icon icon, const QString& title, const QString& text,
    StandardButtons buttons = {StandardButton::NoButton},
    QWidget* parent = nullptr,
    Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint) {

    auto message_box = new QMessageBox{icon, title, text, buttons, parent,
        flags};
    message_box->show();
}

inline void information(const QString& title,
    const QString& text, StandardButtons buttons = {StandardButton::Ok},
    QWidget* parent = nullptr) {

    show(Icon::Information, title, text, buttons, parent);
}


inline void question(const QString& title,
    const QString& text, StandardButtons buttons = {StandardButton::Ok},
    QWidget* parent = nullptr) {

    show(Icon::Question, title, text, buttons, parent);
}

inline void warning(const QString& title,
    const QString& text, StandardButtons buttons = {StandardButton::Ok},
    QWidget* parent = nullptr) {

    show(Icon::Warning, title, text, buttons, parent);
}


inline void critical(const QString& title,
    const QString& text, StandardButtons buttons = {StandardButton::Ok},
    QWidget* parent = nullptr) {

    show(Icon::Critical, title, text, buttons, parent);
}

} // namespace MessageBox
} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // MESSAGEBOX_H_8C2504416242F936
