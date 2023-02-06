#include "Panel.h"
#include "ui_panel.h"

#include <QSplitter>
#include <QLabel>
#include <QBitmap>

namespace WaterwAIs {

namespace {
constexpr auto icon_size = QSize{16, 16};
} // anonymous

//////////////////////////////////////////////////////////////////////////
// PanelTitleLabel

class PanelTitleLabel: public QLabel {
public:
    PanelTitleLabel(QLabel* source_label):
        QLabel{static_cast<QWidget*>(source_label->parent())} {

        // Copying the settings set in the Designer and set in ui->setupUi().
        setObjectName(source_label->objectName());
        setAutoFillBackground(source_label->autoFillBackground());
        setFrameShape(source_label->frameShape());
        setFrameShadow(source_label->frameShadow());
        setText(source_label->text());
    }

protected:
    void mouseDoubleClickEvent(QMouseEvent* /*event*/) override {
        auto panel = qobject_cast<WaterwAIs::Panel*>(parent());
        if (panel)
            panel->onTitleDoubleClicked();
    }
};


//////////////////////////////////////////////////////////////////////////
// Panel

Panel::Panel(QSplitter* parent):
    QFrame(parent),
    ui(new Ui::Panel) {
    ui->setupUi(this);

    splitter_ = parent;

    // Title
    auto panel_label = new PanelTitleLabel{ui->labelTitle};
    ui->horizontalLayout->replaceWidget(ui->labelTitle, panel_label);

    delete ui->labelTitle;
    ui->labelTitle = panel_label;

    auto label_style =
        QStringLiteral("QLabel { background-color : lightgray; color : black; }");

    ui->labelTitle->setStyleSheet(label_style);    

    // Hide Icon
    ui->labelIcon->setStyleSheet(label_style);
    ui->labelIcon->setVisible(false);    

    auto button_style = QStringLiteral(
        "QToolButton { background-color : lightgray; border: none; } "
        "QToolButton:hover {border: 1px solid blue; border-radius: 5px; "
        "background-color: lightblue; }");


    auto set_tool_button = [&](QToolButton* button, QStringView icon_file) {
        button->setIcon(QIcon{icon_file.toString()});
        button->setIconSize(icon_size);
        button->setStyleSheet(button_style);
    };
    
    // Button Close
    set_tool_button(ui->btnClose, u":/Resources/close_green.png");

    // Button Expand
    set_tool_button(ui->btnExpand, u":/Resources/expand-arrow-64.png");

    // Button Collapse
    set_tool_button(ui->btnCollapse, u":/Resources/collapse-arrow-64.png");

    state_ = State::Intermediate;
    setControls();

    connect(splitter_, &QSplitter::splitterMoved, [this](int pos, int index) {
        if (splitter_->indexOf(this) == index) {
            // Our section moved in the splitter
            onSplitterMoved(pos);
        }
    });   
}

Panel::~Panel() {
    setWidget();
    delete ui;
}

void Panel::setTitleText(QStringView title)
    { ui->labelTitle->setText(title.toString()); }

void Panel::setWidget(QWidget* widget) {
    if (!widget)
        widget = ui->placeholder; // Restoring placeholder

    widget->setParent(this);

    auto old_widget = ui->verticalLayout->itemAt(1)->widget();
    ui->verticalLayout->replaceWidget(old_widget, widget);

    if (old_widget != ui->placeholder)
        delete old_widget;
    else
        ui->placeholder->hide();
}

QWidget* Panel::getWidget() const { 
    return ui->verticalLayout->itemAt(1)->widget();
}

void Panel::setIcon(QStringView icon_file) {
    if (icon_file.empty()) {
        // No icon
        ui->labelIcon->hide();
        return;
    }

    auto icon = QIcon{icon_file.toString()};
    auto pixmap = icon.pixmap(icon_size);

    ui->labelIcon->setPixmap(pixmap);
    ui->labelIcon->show();
}

void Panel::setCloseable(bool closeable)
    { ui->btnClose->setVisible(closeable); }

bool Panel::closeable() const
    { return ui->btnClose->isVisible(); }

void Panel::setExpandable(bool expandable)
    { ui->btnExpand->setVisible(expandable); }

bool Panel::expandable() const
    { return ui->btnExpand->isVisible(); }

void Panel::setCollapsible(bool collapsible)
    { ui->btnCollapse->setVisible(collapsible); }

bool Panel::collapsible() const
    { return ui->btnCollapse->isVisible(); }

void Panel::updateState(State new_state) {
    if (state_ != new_state) {
        auto old_state = state_;
        state_ = new_state;

        setControls();
        emit stateChanged(state_, old_state);
    }
}

void Panel::setControls() {
    switch (state_) {
    case State::Intermediate:
        ui->btnExpand  ->show();
        ui->btnCollapse->show();

        ui->btnExpand  ->setToolTip("Expands the panel");
        ui->btnCollapse->setToolTip("Collapses the panel");
        ui->labelTitle ->setToolTip("Double-click to collapse the panel");
        break;

    case State::Expanded:
        ui->btnExpand  ->hide();
        ui->btnCollapse->show();

        ui->btnExpand  ->setToolTip("Expands the panel");
        ui->btnCollapse->setToolTip("Restores the panel");
        ui->labelTitle ->setToolTip("Double-click to restore the panel");
        break;

    case State::Collapsed:
        ui->btnExpand  ->show();
        ui->btnCollapse->hide();

        ui->btnExpand  ->setToolTip("Restores the panel");
        ui->btnCollapse->setToolTip("Collapses the panel");
        ui->labelTitle ->setToolTip("Double-click to restore the panel");
        break;

    default:
        break;
    }
}

void Panel::on_btnCollapse_clicked() {
    collapse();
}

void Panel::on_btnExpand_clicked() {
    expand();
}

void Panel::on_btnClose_clicked() {
    closePanel();
}

void Panel::collapse() {
    if (state_ == State::Collapsed)
        return;

    if (state_ == State::Expanded) {
        // Going to the Intermediate state.
        splitter_->restoreState(splitter_state_);
        updateState(State::Intermediate);
        return;
    }

    if (state_ == State::Intermediate) {
        // Going to the Collapsed state.        
        splitter_state_ = splitter_->saveState();

        auto splitter_sizes = splitter_->sizes();
        auto panel_index = splitter_->indexOf(this);

        auto panel_title_size = titleSize();
        auto widget_size = size() - panel_title_size;
                
        splitter_sizes[panel_index] = panel_title_size.height();

        for (auto i = 0; i < splitter_sizes.size(); i++) {
            if (i != panel_index)
                splitter_sizes[i] += widget_size.height();
        }

        splitter_->setSizes(splitter_sizes);
        updateState(State::Collapsed);
        return;
    }
}

QSize Panel::titleSize() const {
    auto panel_size = size();

    auto widget = ui->verticalLayout->itemAt(1)->widget();
    auto widget_size = widget->size();

    auto title_size = panel_size - widget_size;
    return title_size;
}

void Panel::expand() {
    if (state_ == State::Expanded)
        return;

    if (state_ == State::Collapsed) {
        // Going to the Intermediate state.        
        splitter_->restoreState(splitter_state_);
        updateState(State::Intermediate);
        return;
    }

    if (state_ == State::Intermediate) {
        // Going to the Expanded state.        
        splitter_state_ = splitter_->saveState();

        auto splitter_sizes = splitter_->sizes();
        auto panel_index = splitter_->indexOf(this);

        // Clear splitter indexes for all panels except ours.
        for (auto i = 0; i < splitter_sizes.size(); i++) {
            if (i != panel_index)
                splitter_sizes[i] = 0;
        }

        splitter_->setSizes(splitter_sizes);
        updateState(State::Expanded);
        return;
    }
}

void Panel::closePanel() {
    hide();
    emit panelClosed();
}

void Panel::onSplitterMoved(int /*pos*/) {
    if (state_ == State::Collapsed) {
        // We are resizing the panel, so we are not in the Collapsed state
        // anymore.
        updateState(State::Intermediate);
        return;
    }

    if (state_ == State::Expanded) {        
        // We are resizing the panel, so we are not in the Expanded state
        //anymore.
        updateState(State::Intermediate);        
    }
}

void Panel::onTitleDoubleClicked() {
    switch (state_) {
        case State::Intermediate: collapse(); break;
        case State::Expanded:     collapse(); break;
        case State::Collapsed:      expand(); break;

    default:
        break;
    }
}

} // namespace WaterwAIs