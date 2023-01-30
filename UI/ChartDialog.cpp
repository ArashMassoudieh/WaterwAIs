#include "ChartDialog.h"
#include "ui_chartdialog.h"

#include <UI/ChartView.h>
#include <UI/ChartSettingsDlg.h>

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

ChartDialog::ChartDialog(const ChartInfo& chart_info, QWidget* parent):
    QDialog(parent), chart_info_{chart_info},
    ui(new Ui::ChartDialog) {
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
        
    ui->pushButtonSettings->setIcon(QIcon{":/Resources/settings.png"});
    ui->pushButtonSettings->setText("");
    
    ui->pushButtonReset->setIcon(QIcon{":/Resources/resize.png"});
    ui->pushButtonReset->setText("");

    setWindowIcon(QIcon{":/Resources/chart.png"});

    // Window title
    setWindowTitle("Chart - [" + chart_info_.name() + "]");

    // Creating chart for time series
    createChart();
}

ChartDialog::~ChartDialog() {
    delete ui;
}

void ChartDialog::on_pushButtonSettings_clicked() {
    auto dlg = new ChartSettingsDialog{this};

    connect(dlg, &ChartSettingsDialog::settingsChanged, this,
        [this]() { setupChart(); });

    dlg->setModal(true);
    dlg->show();
}

void ChartDialog::on_pushButtonGo_clicked() {
    auto series = qobject_cast<QLineSeries*>(chart_->series().front());
    Q_ASSERT(series);

    series->clear();

    auto from = ui->lineEditFrom->text().toDouble();
    auto to   = ui->lineEditTo->text().toDouble();

    if (from > to) {
        std::swap(from, to);
        ui->lineEditFrom->setText(QString::number(from, 'f', 2));
        ui->lineEditTo  ->setText(QString::number(to, 'f', 2));
    }

    // Filling series
    auto ts = chart_info_.timeSeries();
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

void ChartDialog::on_pushButtonReset_clicked() {
    ui->lineEditFrom->setText(QString::number(min_t_, 'f', 2));
    ui->lineEditTo  ->setText(QString::number(max_t_, 'f', 2));
}

void ChartDialog::createChart() {
    chart_ = new QChart{};
    chart_->setTitle(chart_info_.name());

    auto series = new QLineSeries{chart_};
    series->setName("Values");

    // Filling series
    auto ts = chart_info_.timeSeries();
    auto count = std::min(ts.CSize(), ts.tSize());

    for (auto i = 0; i < count; i++)
        series->append(ts.GetT(i), ts.GetC(i));

    chart_->addSeries(series);

    min_t_ = ts.mint();
    max_t_ = ts.maxt();

    chart_->createDefaultAxes();
    chart_->axes(Qt::Horizontal).first()->setRange(min_t_, max_t_);
    chart_->axes(Qt::Vertical  ).first()->setRange(ts.minC(), ts.maxC());

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
}


void ChartDialog::setupChart() {
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

} // namespace WaterwAIs
