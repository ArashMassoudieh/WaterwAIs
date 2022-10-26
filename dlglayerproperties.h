#ifndef DLGLAYERPROPERTIES_H
#define DLGLAYERPROPERTIES_H

#include <QDialog>
#include "layer.h"

namespace Ui {
class DlgLayerProperties;
}

class DlgLayerProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLayerProperties(Layer *layer, QWidget *parent = nullptr);
    ~DlgLayerProperties();

public slots:
    void on_btnColor_clicked();
    void on_sldTransparency_valueChanged(int val);
    void on_chkVisible_stateChanged(int state);
    void on_sbSymbolSize_valueChanged(int val);
    void onCbLineTypeCurrentIndexChanged(int index);

private:
    Ui::DlgLayerProperties *ui;
    Layer *layer;

    void updateBtnColor();
    void updateLineStyle();
};

#endif // DLGLAYERPROPERTIES_H
