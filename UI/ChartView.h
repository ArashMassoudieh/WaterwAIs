
#ifndef CHARTVIEW_H_8B6E4DAAD453DEA0
#define CHARTVIEW_H_8B6E4DAAD453DEA0

#include <QWidget>
#include <QChartView>
#include <QChart>



#ifndef Qt6
using namespace QtCharts;
#endif

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// ChartSettings

class ChartSettings {
public:
    QChart::ChartTheme theme = QChart::ChartThemeLight;
    int  legend = 0; // No Legend
    bool anti_aliasing = false;
};


//////////////////////////////////////////////////////////////////////////
// ChartView

class ChartView: public QChartView {
    Q_OBJECT
public:
    explicit ChartView(QWidget* parent = nullptr);
    explicit ChartView(QChart* chart, QWidget* parent = nullptr);

    static ChartSettings& chartSettings();

private:
};

} // namespace WaterwAIs


//////////////////////////////////////////////////////////////////////////
#endif // CHARTVIEW_H_8B6E4DAAD453DEA0