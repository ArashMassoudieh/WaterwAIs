#ifndef PANEL_H_A5E138B573C369CD
#define PANEL_H_A5E138B573C369CD

#include <QFrame>

namespace Ui {
class Panel;
}

class QSplitter;

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// Panel

class Panel: public QFrame {
    Q_OBJECT    
public:
    friend class PanelTitleLabel;

    enum class State {
        Intermediate = 0,
        Expanded,
        Collapsed
    };

    explicit Panel(QSplitter* parent = nullptr);
    ~Panel();

    // Title
    void setTitleText(QStringView title);

    // Icon
    void setIcon(QStringView icon_file);

    // Widget
    void setWidget(QWidget* widget = nullptr);
    QWidget* getWidget() const;

    // Closeable
    void setCloseable(bool closeable);  
    bool closeable() const;

    // Expandable
    void setExpandable(bool expandable);
    bool expandable() const;

    // Collapsible
    void setCollapsible(bool collapsible);
    bool collapsible() const;

    // State
    State state() const { return state_; }        

    // Operations
public slots:
    void collapse();
    void expand();
    void closePanel();

signals:
    void stateChanged(State new_state, State old_state);
    void panelClosed();

protected:
    void onSplitterMoved(int pos);

private slots:
    void on_btnClose_clicked();
    void on_btnExpand_clicked();
    void on_btnCollapse_clicked();

private:
    QSize titleSize() const;
    void updateState(State new_state);
      
    void setControls();    

    void onTitleDoubleClicked();

    QList<int> restore_info_;
    State state_;

    QByteArray splitter_state_;
    QSplitter* splitter_ = nullptr;

    Ui::Panel* ui;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // PANEL_H_A5E138B573C369CD
