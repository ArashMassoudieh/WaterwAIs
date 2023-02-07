#include "ChartView.h"

namespace WaterwAIs {

namespace {
ChartSettings chart_settings;
} // anonymous


//////////////////////////////////////////////////////////////////////////
// ChartView

ChartView::ChartView(QWidget* parent): QChartView{parent} {
}

ChartView::ChartView(QChart* chart, QWidget* parent)
    : QChartView{chart, parent} {
}

ChartSettings& ChartView::chartSettings() {
    return chart_settings;
}

} // namespace WaterwAIs