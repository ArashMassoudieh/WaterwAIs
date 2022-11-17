#include <QDebug>
#include <QColorDialog>
#include "dlglayerproperties.h"
#include "ui_dlglayerproperties.h"

DlgLayerProperties::DlgLayerProperties(Layer *layer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLayerProperties),
    layer(layer)
{
    ui->setupUi(this);
    ui->cbLineType->addItems(
                QStringList {
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
    ui->sldTransparency->setValue(layer->layerOpacity() * 100);
    ui->sbSymbolSize->setValue(layer->Pen().width());

    connect(ui->cbLineType, SIGNAL(currentIndexChanged()), this, SLOT(onCbLineTypeCurrentIndexChanged()));
}

DlgLayerProperties::~DlgLayerProperties()
{
    delete ui;
}

void DlgLayerProperties::on_btnColor_clicked()
{
    auto dlg = new QColorDialog();
    connect(dlg, &QColorDialog::colorSelected, this, [this, dlg](const QColor &color) {
        if (color.isValid()) {
            layer->SetColor(color);
            updateBtnColor();
        }

        dlg->deleteLater();
    });
    dlg->open();
}

void DlgLayerProperties::on_sldTransparency_valueChanged(int val)
{
    layer->setOpacity(val / 100.0);
}

void DlgLayerProperties::on_chkVisible_stateChanged(int state)
{
    layer->setVisible(state == Qt::Checked);
}

void DlgLayerProperties::on_sbSymbolSize_valueChanged(int val)
{
    layer->setLineWidth(val);
}

void DlgLayerProperties::onCbLineTypeCurrentIndexChanged(int index)
{
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

void DlgLayerProperties::updateBtnColor()
{
    QPixmap px(32, 32);
    px.fill(layer->layerColor());
    ui->btnColor->setIcon(px);
}

void DlgLayerProperties::updateLineStyle()
{
    auto style = layer->Pen().style();
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
