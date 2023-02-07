#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QFrame>
#include <QChart>

#include <Utilities/TimeSeries_s.h>
#include <MetaModelLayer/Variable.h>

namespace Ui {
class ChartWidget;
}

#include <QtGlobal>
#if QT_VERSION < 0x060000
    using namespace QtCharts;
#endif

class QLabel;

namespace WaterwAIs {

class ChartView;

//////////////////////////////////////////////////////////////////////////
// ChartInfo

class ChartInfo {
public:
    using TimeSeries = CTimeSeries<double>;
    using TimeSeriesPtr = std::shared_ptr<const TimeSeries>;

    ChartInfo(QStringView name, QStringView time_series_path) :
        name_{name.toString()}, 
        time_series_path_{time_series_path.toString()} {}

    QString name() const { return name_; }
    QString timeSeriesPath() const { return time_series_path_; }   

    bool operator==(const ChartInfo& other) const { return  equalTo(other); }
    bool operator!=(const ChartInfo& other) const { return !equalTo(other); }

    bool equalTo(const ChartInfo& other) const  {
        return name_ == other.name_ && 
            time_series_path_ == other.time_series_path_;
    }

private:
    QString name_;
    QString time_series_path_;
};


//////////////////////////////////////////////////////////////////////////
// ChartDialog

class ChartWidget : public QFrame {
    Q_OBJECT

public:
    explicit ChartWidget(const ChartInfo& chart_info, QWidget *parent = nullptr);
    ~ChartWidget();    

    const ChartInfo& chartInfo() const { return chart_info_; }

    QSize minimumSizeHint() const override;

public slots:
    void setupChart();

protected slots:
    void on_toolButtonSettings_clicked();
    void on_pushButtonGo_clicked();
    void on_toolButtonReset_clicked();    

private:
    using TimeSeriesPtr = ChartInfo::TimeSeriesPtr;

    void createChart();    
    void fillChart();
    void fillSeries();

    void showStatusText(QStringView status);
    void hideStatusText();

    void enableChartControls(bool enable = true);

    const ChartInfo& chart_info_;
    QChart* chart_;

    double min_t_ = 0.0;
    double max_t_ = 0.0;

    TimeSeriesPtr tseries_;

    QLabel* status_label_ = nullptr;
    Ui::ChartWidget *ui;
};

} // namespace WaterwAIs

#endif // CHARTDIALOG_H
