#ifndef ITEMPROPERTIESWIDGET_H_9DE3B491A3066902
#define ITEMPROPERTIESWIDGET_H_9DE3B491A3066902

#include "ItemNavigator.h"

#include <QFrame>
#include <MetaModelLayer/MetaItemPropertyModel.h>
#include <memory>

class QSortFilterProxyModel;
class QToolButton;

namespace Ui {
class ItemPropertiesWidget;
}

namespace WaterwAIs {

class MetaLayerItem;
class ItemNavigator;

//////////////////////////////////////////////////////////////////////////
// ItemPropertiesWidget

class ItemPropertiesWidget: public QFrame, public ItemNavigatorHolder {
    Q_OBJECT
public:
    explicit ItemPropertiesWidget(QWidget* parent = nullptr);
    ~ItemPropertiesWidget();
    
    // Property model
    void setTableModel(MetaItemPropertyModel* propmodel = nullptr);
    
    QSize minimumSizeHint() const override;

signals:
    void showTimeSeries(QStringView item_name, QStringView prop_name,
        QStringView ts_path, ItemNavigatorPtr item_navigator);
    
protected slots:
    void on_btnNavigate_clicked();
    void on_edtFilter_textChanged(const QString& text);

    // ItemNavigatorHolder
    void onNavigatorSet() override;

private:
    void setupControls();
    void onButtonWidgetClicked(int prop_index);

    Ui::ItemPropertiesWidget* ui;
    QToolButton* btnNavigate_ = nullptr;

    QSortFilterProxyModel* prop_proxy_model_ = nullptr;
    MetaItemPropertyModel* prop_model_       = nullptr;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // ITEMPROPERTIESWIDGET_H_9DE3B491A3066902
