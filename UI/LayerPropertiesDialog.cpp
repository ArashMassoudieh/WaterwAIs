#include <QDebug>
#include <QColorDialog>
#include "LayerPropertiesDialog.h"
#include "ui_dlglayerproperties.h"

namespace WaterWays {

///////////////////////////////////////////////////////////////////////////
// LayerPropertiesDialog

LayerPropertiesDialog::LayerPropertiesDialog(Layer* layer, QWidget* parent):
    QDialog(parent),
    ui(new Ui::DlgLayerProperties),
    layer(layer) {
    ui->setupUi(this);
    ui->cbLineType->addItems(
        QStringList{
            "None",
            "Solid",
            "Dash",
            "Dot",
            "DashDot",
            "DashDotDot",
        });

    updateBtnColor();
    updateLineStyle();
    ui->chkVisible->setChecked(layer->visible());
    ui->sldTransparency->setValue(layer->opacity() * 100);
    ui->sbSymbolSize->setValue(layer->settings().pen.width());   

    // Title and Icon
    setWindowTitle(layer->name() + " Properties");
    setWindowIcon (layer->icon());

    connect(ui->cbLineType, SIGNAL(currentIndexChanged(int)), this,
        SLOT(onCbLineTypeCurrentIndexChanged(int)));
}

LayerPropertiesDialog::~LayerPropertiesDialog() {
    delete ui;
}

void LayerPropertiesDialog::on_btnColor_clicked() {
    auto dlg = new QColorDialog{};

    connect(dlg, &QColorDialog::colorSelected, this,
        [this, dlg](const QColor& color) {
            if (color.isValid()) {
                layer->setColor(color);
                updateBtnColor();
            }

            dlg->deleteLater();
        });

    dlg->open();
}

void LayerPropertiesDialog::on_sldTransparency_valueChanged(int val) {
    layer->setOpacity(val / 100.0);
}

void LayerPropertiesDialog::on_chkVisible_stateChanged(int state) {
    layer->setVisible(state == Qt::Checked);
}

void LayerPropertiesDialog::on_sbSymbolSize_valueChanged(int val) {
    layer->setLineWidth(val);
}

void LayerPropertiesDialog::onCbLineTypeCurrentIndexChanged(int index) {
    switch (index) {
    case 0:
        layer->setLineType(Qt::NoPen);
        break;

    case 1:
        layer->setLineType(Qt::SolidLine);
        break;

    case 2:
        layer->setLineType(Qt::DashLine);
        break;

    case 3:
        layer->setLineType(Qt::DotLine);
        break;

    case 4:
        layer->setLineType(Qt::DashDotLine);
        break;

    case 5:
        layer->setLineType(Qt::DashDotDotLine);
        break;
    }
}

void LayerPropertiesDialog::updateBtnColor() {
    auto icon = QPixmap{32, 32};
    icon.fill(layer->color());
    ui->btnColor->setIcon(icon);
}

void LayerPropertiesDialog::updateLineStyle() {
    auto style = layer->settings().pen.style();
    switch (style) {
    case Qt::NoPen:
        ui->cbLineType->setCurrentText("None");
        break;

    case Qt::SolidLine:
        ui->cbLineType->setCurrentText("Solid");
        break;

    case Qt::DashLine:
        ui->cbLineType->setCurrentText("Dash");
        break;

    case Qt::DotLine:
        ui->cbLineType->setCurrentText("Dot");
        break;

    case Qt::DashDotLine:
        ui->cbLineType->setCurrentText("DashDot");
        break;

    case Qt::DashDotDotLine:
        ui->cbLineType->setCurrentText("DashDotDot");
        break;
    }
}


} // namespace WaterWays