#include "MessageBox.h"

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// MessageBox

MessageBox::MessageBox(QWidget* parent)
    : QMessageBox{parent} {
}

MessageBox::MessageBox(Icon icon, const QString& title, const QString& text,
    StandardButtons buttons, QWidget* parent, Qt::WindowFlags flags):
    QMessageBox{icon, title, text, buttons, parent, flags} {
}

MessageBox::~MessageBox() {
}

void MessageBox::showMsg(Icon icon, const QString& title, const QString& text,
    StandardButtons buttons, QWidget* parent,  Qt::WindowFlags flags) {

    auto message_box = 
        new MessageBox{icon, title, text, buttons, parent, flags};

    message_box->show();
}


void MessageBox::showEvent(QShowEvent* /*event*/) {
    if (auto_close_)        
        startTimer(close_timeout_);
}

void MessageBox::timerEvent(QTimerEvent* /*event*/) {
    done(0);
}


} // namespace WaterwAIs