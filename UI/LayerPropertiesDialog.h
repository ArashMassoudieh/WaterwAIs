#ifndef DLGLAYERPROPERTIES_H
#define DLGLAYERPROPERTIES_H

#include <QDialog>
#include <Layer/Layer.h>

namespace Ui {
class DlgLayerProperties;
}

namespace WaterwAIs {

///////////////////////////////////////////////////////////////////////////
// LayerPropertiesDialog

class LayerPropertiesDialog: public QDialog {
    Q_OBJECT

public:
    explicit LayerPropertiesDialog(Layer* layer, QWidget* parent = nullptr);
    ~LayerPropertiesDialog();

public slots:
    void on_btnColor_clicked();
    void on_sldTransparency_valueChanged(int val);
    void on_chkVisible_stateChanged(int state);
    void on_sbSymbolSize_valueChanged(int val);
    void onCbLineTypeCurrentIndexChanged(int index);

private:
    Ui::DlgLayerProperties* ui;
    Layer* layer;

    void updateBtnColor();
    void updateLineStyle();
};

} // namespace WaterwAIs

#endif // DLGLAYERPROPERTIES_H
