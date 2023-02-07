
#include "ChartWidget.h"
#include "ui_chartwidget.h"

#include "ChartView.h"
#include "ChartSettingsDlg.h"

#include <Application/TimeSeriesCache.h>

#include <QLineSeries>
#include <QChart>
#include <QValueAxis>
#include <QDoubleValidator>

namespace WaterwAIs {

namespace {

class RangeFromValidator: public QDoubleValidator {
public:
    RangeFromValidator(double bottom, double top, int decimals,
        QObject* parent = nullptr)
        :QDoubleValidator(bottom, top, decimals, parent) {
    }

    virtual void fixup(QString& input)const override {
        input = QString::number(bottom(), 'f', decimals());
    }
};

class RangeToValidator: public QDoubleValidator {
public:
    RangeToValidator(double bottom, double top, int decimals,
        QObject* parent = nullptr)
        :QDoubleValidator(bottom, top, decimals, parent) {
    }

    virtual void fixup(QString& input)const override {
        input = QString::number(top(), 'f', decimals());
    }
};

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

    setWindowIcon(QIcon{":/Resources/chart.png"});   

    // Creating chart for time series
    createChart();
}

ChartWidget::~ChartWidget() {
    hideStatusText();
    delete ui;
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
    auto from = ui->lineEditFrom->text().toDouble();
    auto to   = ui->lineEditTo->text().toDouble();

    if (from > to) {
        std::swap(from, to);
        ui->lineEditFrom->setText(QString::number(from, 'f', 2));
        ui->lineEditTo->setText(QString::number(to, 'f', 2));
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

    for (auto i = 0; i < count; i++) {
        auto time = ts.GetT(i);
        if (time > to)
            break;

        if (time >= from) {
            auto value = ts.GetC(i);

            if (first_value) {
                min_value = value;
                max_value = value;

                first_value = false;
            }

            min_value = std::min(min_value, value);
            max_value = std::max(max_value, value);

            series->append(time, value);
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
        series->append(ts.GetT(i), ts.GetC(i));

    chart_->addSeries(series);

    min_t_ = ts.mint();
    max_t_ = ts.maxt();

    chart_->createDefaultAxes();
    chart_->axes(Qt::Horizontal).first()->setRange(min_t_, max_t_);
    chart_->axes(Qt::Vertical).first()->setRange(ts.minC(), ts.maxC());

    // Add space to label to add space between labels and axis
    auto axis_x = qobject_cast<QValueAxis*>(chart_->axes(Qt::Horizontal).first());
    axis_x->setLabelFormat("%.2f  ");
    //axis_x->setTitleText("time");

    auto axis_y = qobject_cast<QValueAxis*>(chart_->axes(Qt::Vertical).first());
    axis_y->setLabelFormat("%.2f  ");

    setupChart();
    ui->chartView->setChart(chart_);

    // Updating From/To
    ui->lineEditFrom->setText(QString::number(min_t_, 'f', 2));
    ui->lineEditFrom->setValidator(new RangeFromValidator(min_t_, max_t_, 2,
        ui->lineEditFrom));

    ui->lineEditTo->setText(QString::number(max_t_, 'f', 2));
    ui->lineEditTo->setValidator(new RangeToValidator(min_t_, max_t_, 2,
        ui->lineEditTo));

    // Enable chart-related controls as chart is ready.
    enableChartControls(); 
}


void ChartWidget::on_toolButtonReset_clicked() {
    ui->lineEditFrom->setText(QString::number(min_t_, 'f', 2));
    ui->lineEditTo  ->setText(QString::number(max_t_, 'f', 2));

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
    chart_->setTitle(chart_info_.name());

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

} // namespace WaterwAIs
