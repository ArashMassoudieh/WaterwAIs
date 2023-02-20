#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QFrame>
#include <QChart>
#include <QDateTime>

#include <Utilities/TimeSeries_s.h>
#include <MetaModelLayer/Variable.h>
#include <UI/ItemNavigator.h>

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
class MetaLayerItem;
class ItemNavigator;

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

    bool equalTo(const ChartInfo& other) const  {
        return name_ == other.name_ && 
            time_series_path_ == other.time_series_path_;
    }

private:
    QString name_;
    QString time_series_path_;
};


//////////////////////////////////////////////////////////////////////////
// ChartWidget

class ChartWidget : public QFrame, public ItemNavigatorHolder {
    Q_OBJECT

public:
    using ItemNavigatorPtr = std::shared_ptr<ItemNavigator>;

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
    void on_toolButtonNav_clicked();

    // ItemNavigatorHolder
    void onNavigatorSet() override;

private:
    using TimeSeriesPtr = ChartInfo::TimeSeriesPtr;

    void createChart();    
    void fillChart();
    void fillSeries();

    void showStatusText(QStringView status);
    void hideStatusText();

    void enableChartControls(bool enable = true);

    ChartInfo chart_info_;
    QChart* chart_;

    QDateTime min_t_;
    QDateTime max_t_;

    TimeSeriesPtr tseries_;

    QLabel* status_label_ = nullptr;
    Ui::ChartWidget *ui;
};

} // namespace WaterwAIs

#endif // CHARTDIALOG_H
