
#include "ChartWidget.h"
#include "ui_chartwidget.h"

#include "ChartView.h"
#include "ChartSettingsDlg.h"

#include <Application/TimeSeriesCache.h>
#include <MetaModelLayer/MetaLayerItem.h>

#include <QStyle>
#include <QLineSeries>
#include <QChart>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QDoubleValidator>

namespace WaterwAIs {

namespace {

static constexpr auto date_format  = "MM-dd-yyyy hh:mm";
static constexpr auto input_format = "MM-dd-yyyy hh:mm";

// This function takes the number of days since 12/30/1899 00:00:00
// and converts it into a number of msecs since Epoch needed to cunstruct
// QDateTime instances for charts.
double toMSecsSinceEpoch(double days) {
    return (days * 86400 - 2209161600) * 1000;
}

// This function returns the number of days since 12/30/1899 00:00:00
// from QDateTime value.
double daysFromDateTime(const QDateTime dt) {
    auto secs_epoch = static_cast<double>(dt.toSecsSinceEpoch());
    return (secs_epoch + 2209161600) / 86400;
}

} // anonymous


//////////////////////////////////////////////////////////////////////////
// ChartDialog

ChartWidget::ChartWidget(const ChartInfo& chart_info, QWidget* parent):
    QFrame{parent}, chart_info_{chart_info},
    ui(new Ui::ChartWidget) {
    ui->setupUi(this);
        
    ui->toolButtonSettings->setIcon(QIcon{":/Resources/settings.png"});
    ui->toolButtonSettings->setText("");
    
    ui->toolButtonReset->setIcon(QIcon{":/Resources/resize.png"});
    ui->toolButtonReset->setText("");
    
    auto icon = QApplication::style()->standardIcon(QStyle::SP_CommandLink);
    ui->toolButtonNav->setIcon(icon);    

    ui->lineEditFrom->setDisplayFormat(input_format);
    ui->lineEditTo  ->setDisplayFormat(input_format);

    setWindowIcon(QIcon{":/Resources/chart.png"});

    // Creating chart for time series
    createChart();
}

ChartWidget::~ChartWidget() {
    hideStatusText();
    delete ui;
}

void ChartWidget::onNavigatorSet() {
    ui->toolButtonNav->setIcon(ItemNavigatorHolder::icon());
}

void ChartWidget::on_toolButtonSettings_clicked() {
    auto dlg = new ChartSettingsDialog{this};

    connect(dlg, &ChartSettingsDialog::settingsChanged, this,
        [this]() { setupChart(); });

    dlg->setModal(true);
    dlg->show();
}

void ChartWidget::on_pushButtonGo_clicked() {
    // Filling series
    fillSeries();
}

void ChartWidget::fillSeries() {
    auto from = ui->lineEditFrom->dateTime();
    auto to   = ui->lineEditTo  ->dateTime();

    qDebug() << "from: " << from;
    qDebug() << "to  : " << to;

    if (from > to) {
        std::swap(from, to);
        
        ui->lineEditFrom->setDateTime(from);
        ui->lineEditTo  ->setDateTime(to);
    }

    auto series = qobject_cast<QLineSeries*>(chart_->series().front());
    Q_ASSERT(series);

    series->clear();

    if (!tseries_)
        return;

    auto& ts = *tseries_;
    auto count = std::min(ts.CSize(), ts.tSize());

    auto min_value = 0.0;
    auto max_value = 0.0;
    auto first_value = true;

    auto from_days = daysFromDateTime(from);
    auto to_days   = daysFromDateTime(to);

    for (auto i = 0; i < count; i++) {
        auto time = ts.GetT(i);
        if (time > to_days)
            break;

        if (time >= from_days) {
            auto value = ts.GetC(i);

            if (first_value) {
                min_value = value;
                max_value = value;

                first_value = false;
            }

            min_value = std::min(min_value, value);
            max_value = std::max(max_value, value);

            series->append(toMSecsSinceEpoch(time), value);
        }
    }

    // Setting ranges
    chart_->axes(Qt::Horizontal).first()->setRange(from, to);
    chart_->axes(Qt::Vertical  ).first()->setRange(min_value, max_value);
}

void ChartWidget::fillChart() {
    if (!tseries_) {
        showStatusText(u"Failed to download chart data");
        return;
    }    

    auto& ts = *tseries_;
    auto count = std::min(ts.CSize(), ts.tSize());

    if (!count) {
        showStatusText(u"Empty chart data");
        return;
    }

    hideStatusText();

    auto series = qobject_cast<QLineSeries*>(chart_->series().front());
    Q_ASSERT(series);    

    for (auto i = 0; i < count; i++)
        series->append(toMSecsSinceEpoch(ts.GetT(i)), ts.GetC(i));    

    auto axisX = new QDateTimeAxis{};
    axisX->setFormat(date_format);
    
    min_t_.setMSecsSinceEpoch(toMSecsSinceEpoch(ts.mint()));
    max_t_.setMSecsSinceEpoch(toMSecsSinceEpoch(ts.maxt()));

    axisX->setRange(min_t_, max_t_);

    //axisX->setTickCount(5);
    //axisX->setTitleText("time");

    chart_->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis{};
    axisY->setLabelFormat("%.2f  ");
    axisY->setRange(ts.minC(), ts.maxC());

    chart_->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    setupChart();
    ui->chartView->setChart(chart_);

    // Updating From/To
    ui->lineEditFrom->setDateTime(min_t_);    
    ui->lineEditFrom->setDateTimeRange(min_t_, max_t_);

    ui->lineEditTo->setDateTime(max_t_);
    ui->lineEditTo->setDateTimeRange(min_t_, max_t_);

    // Enable chart-related controls as chart is ready.
    enableChartControls(); 
}


void ChartWidget::on_toolButtonReset_clicked() {
    ui->lineEditFrom->setDateTime(min_t_);
    ui->lineEditTo  ->setDateTime(max_t_);

    fillSeries();
}

void ChartWidget::enableChartControls(bool enable) {
    // Enable/disable chart-related controls.
    ui->lineEditFrom      ->setEnabled(enable);
    ui->lineEditTo        ->setEnabled(enable);
    ui->pushButtonGo      ->setEnabled(enable);
    ui->toolButtonReset   ->setEnabled(enable);
    ui->toolButtonSettings->setEnabled(enable);
}

void ChartWidget::createChart() {
    // Disable chart-related controls until chart is ready
    enableChartControls(false);

    // Creating chart
    chart_ = new QChart{};

    auto series = new QLineSeries{chart_};
    series->setName("Values");

    chart_->addSeries(series);

    // Filling chart
    tseries_.reset();

    auto& ts_cache = TimeSeriesCache::instance();
    tseries_ = ts_cache.get(chart_info_.timeSeriesPath(), [this](auto ts) {
        tseries_ = ts;
        fillChart();        
    });

    if (tseries_) {
        // We found time series in the cache, so we can fill the chart.
        fillChart();       
    } else {
        // We need to wait until time series are downloaded.
        showStatusText(u"Downloading chart data, please wait...");
    }   
}


void ChartWidget::setupChart() {
    // Settings
    auto& settings = ChartView::chartSettings();

    // Title        
    chart_->setTitle(settings.title ? chart_info_.name() : "");

    // Theme
    chart_->setTheme(settings.theme);

    // Legend
    auto legend = chart_->legend();

    if (!settings.legend) {
        legend->hide();
    } else {
        auto alignment = Qt::Alignment{settings.legend};
        legend->setAlignment(alignment);
        legend->show();
    }
}

void ChartWidget::showStatusText(QStringView status) {
    if (!status_label_) {
        status_label_ = new QLabel{this};
        status_label_->setAlignment(Qt::AlignCenter);

        ui->verticalLayout->replaceWidget(ui->chartView, status_label_);
        ui->chartView->hide();
    }

    // We are displaying the status text already.
    status_label_->setText(status.toString());
}


void ChartWidget::hideStatusText() {
    if (!status_label_)
        return;

    ui->verticalLayout->replaceWidget(status_label_, ui->chartView);
    ui->chartView->show();

    delete status_label_;
    status_label_ = nullptr;
}

QSize ChartWidget::minimumSizeHint() const {
    // This ensures that we can collapse the channel widget to 0 size.
    return {0, 0};
}

void ChartWidget::on_toolButtonNav_clicked() {
    navigate();
}


} // namespace WaterwAIs
