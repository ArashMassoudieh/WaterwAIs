#ifndef CHARTSETTINGSDLG_H_8B35D0E364EB3F5A
#define CHARTSETTINGSDLG_H_8B35D0E364EB3F5A

#include <QDialog>
#include <UI/ChartView.h>

namespace Ui {
class ChartSettingsDialog;
}

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// ChartSettingsDialog

class ChartSettingsDialog: public QDialog {
    Q_OBJECT

public:
    explicit ChartSettingsDialog(QWidget* parent = nullptr);
    ~ChartSettingsDialog();

signals:
    void settingsChanged();

protected:
    void accept() override;
    void reject() override;

private slots:
    void changed();

private:
    void fill();

    bool ignore_changed_ = true;
    ChartSettings orig_settings_;

    Ui::ChartSettingsDialog* ui;    
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // CHARTSETTINGSDLG_H_8B35D0E364EB3F5A
