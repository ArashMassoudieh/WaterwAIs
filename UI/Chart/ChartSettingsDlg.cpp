#include "ChartSettingsDlg.h"
#include "ui_chartsettingsdialog.h"

#include <QChart>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// ChartSettingsDialog

ChartSettingsDialog::ChartSettingsDialog(QWidget* parent):
    QDialog{parent}, orig_settings_{ChartView::chartSettings()},
    ui{new Ui::ChartSettingsDialog} {
    ui->setupUi(this);

    // Allow only horizontal resizing.
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    // Filling controls
    fill();
}

ChartSettingsDialog::~ChartSettingsDialog() {
    delete ui;
}

void ChartSettingsDialog::fill() {
    // Ignoring changed signals until we are done with filling.
    ignore_changed_ = true;

    auto& settings = ChartView::chartSettings();

    // Title
    ui->checkBoxTitle->setChecked(settings.title);

    // Theme Combobox    
    ui->comboBoxTheme->addItem("Light"        , QChart::ChartThemeLight);
    ui->comboBoxTheme->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->comboBoxTheme->addItem("Dark"         , QChart::ChartThemeDark);
    ui->comboBoxTheme->addItem("Brown Sand"   , QChart::ChartThemeBrownSand);
    ui->comboBoxTheme->addItem("Blue NCS"     , QChart::ChartThemeBlueNcs);
    ui->comboBoxTheme->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->comboBoxTheme->addItem("Blue Icy"     , QChart::ChartThemeBlueIcy);
    ui->comboBoxTheme->addItem("Qt"           , QChart::ChartThemeQt);

    ui->comboBoxTheme->setCurrentIndex(static_cast<int>(settings.theme));

    // Legend combobox    
    ui->comboBoxLegend->addItem("No Legend "   , 0);
    ui->comboBoxLegend->addItem("Legend Top"   , Qt::AlignTop);
    ui->comboBoxLegend->addItem("Legend Bottom", Qt::AlignBottom);
    ui->comboBoxLegend->addItem("Legend Left"  , Qt::AlignLeft);
    ui->comboBoxLegend->addItem("Legend Right" , Qt::AlignRight);

    auto legend_idx = 0;

    switch (settings.legend) {
        case Qt::AlignTop   : legend_idx = 1; break;
        case Qt::AlignBottom: legend_idx = 2; break;
        case Qt::AlignLeft  : legend_idx = 3; break;
        case Qt::AlignRight : legend_idx = 4; break;
    default:
        break;
    }

    ui->comboBoxLegend->setCurrentIndex(legend_idx);

    // Anti-aliasing
    ui->checkBoxAntiAliasing->setChecked(settings.anti_aliasing);

    ignore_changed_ = false;
}

void ChartSettingsDialog::changed() {
    if (ignore_changed_)
        return;    

    // Update settings
    auto& settings = ChartView::chartSettings();

    // Title
    settings.title = ui->checkBoxTitle->isChecked();

    // Theme
    settings.theme = static_cast<QChart::ChartTheme>(
        ui->comboBoxTheme->itemData(ui->comboBoxTheme->currentIndex()).toInt());

    // Legend
    settings.legend =
        ui->comboBoxLegend->itemData(ui->comboBoxLegend->currentIndex()).toInt();

    // Anti-aliasing
    settings.anti_aliasing = ui->checkBoxAntiAliasing->isChecked();

    emit settingsChanged();
}

void ChartSettingsDialog::accept() {
    changed();
    done(0);
}

void ChartSettingsDialog::reject() {
    // Restoring original settings
    ChartView::chartSettings() = orig_settings_;

    emit settingsChanged();
    done(0);
}


} // namespace WaterwAIs
