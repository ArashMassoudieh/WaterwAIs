#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QChart>

#include <MetaModelLayer/Variable.h>

namespace Ui {
class ChartDialog;
}

#ifndef Qt6
using namespace QtCharts;
#endif

namespace WaterwAIs {

class ChartView;

//////////////////////////////////////////////////////////////////////////
// ChartInfo

class ChartInfo {
public:
    ChartInfo(QString name, const TimeSeries& time_series) :
        name_{std::move(name)}, time_series_{time_series} {}

    QString name() const { return name_; }
    const TimeSeries& timeSeries() const { return time_series_; }

private:
    QString name_;
    const TimeSeries& time_series_;
};


//////////////////////////////////////////////////////////////////////////
// ChartDialog

class ChartDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChartDialog(const ChartInfo& chart_info, QWidget *parent = nullptr);
    ~ChartDialog();    

public slots:
    void setupChart();

protected slots:
    void on_pushButtonSettings_clicked();
    void on_pushButtonGo_clicked();
    void on_pushButtonReset_clicked();

private:
    void createChart();

    const ChartInfo& chart_info_;
    QChart* chart_;

    double min_t_ = 0.0;
    double max_t_ = 0.0;

    Ui::ChartDialog *ui;
};

} // namespace WaterwAIs

#endif // CHARTDIALOG_H
