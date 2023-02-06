#ifndef ITEMPROPERTIESWIDGET_H_9DE3B491A3066902
#define ITEMPROPERTIESWIDGET_H_9DE3B491A3066902

#include <QFrame>
#include <MetaModelLayer/MetaItemPropertyModel.h>

class QSortFilterProxyModel;

namespace Ui {
class ItemPropertiesWidget;
}

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// ItemPropertiesWidget

class ItemPropertiesWidget: public QFrame {
    Q_OBJECT

public:
    explicit ItemPropertiesWidget(QWidget* parent = nullptr);
    ~ItemPropertiesWidget();

    void setTableModel(MetaItemPropertyModel* propmodel = nullptr);

    QSize minimumSizeHint() const override;

signals:
    void showTimeSeries(QStringView item_name, QStringView prop_name,
        QStringView ts_path);

protected slots:
    void on_edtFilter_textChanged(const QString& text);

private:
    void onButtonWidgetClicked(int prop_index);

    Ui::ItemPropertiesWidget* ui;

    QSortFilterProxyModel* prop_proxy_model_ = nullptr;
    MetaItemPropertyModel* prop_model_ = nullptr;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // ITEMPROPERTIESWIDGET_H_9DE3B491A3066902
