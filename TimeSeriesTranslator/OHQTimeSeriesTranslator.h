
#ifndef OHQTimeSeriesTranslator_H_B6055E29C4BC6BF8
#define OHQTimeSeriesTranslator_H_B6055E29C4BC6BF8

#include "TimeSeriesSet_s.h"

#include <QObject>
#include <QTimer>

#include <chrono>
#include <memory>
#include <string>

namespace WaterwAIs {

using namespace std::chrono_literals;

class TestTSBuilder;

//////////////////////////////////////////////////////////////////////////
// OHQTimeSeriesTranslator

class OHQTimeSeriesTranslator: public QObject {
    Q_OBJECT
public:
    explicit OHQTimeSeriesTranslator(QObject* parent = nullptr);
    ~OHQTimeSeriesTranslator();

    // Run translation in the main working mode.
    void run(QStringView cfg_file = {});

    // Run translation in the test mode.
    void runTest(QStringView test_cfg_file = {});

signals:

public slots:
    void translate();

private:
    using TimeSeriesSet = CTimeSeriesSet<double>;
    using TimeSeries    = CTimeSeries<double>;

    bool readConfig(const QString& config_file);
    void runTranslation();
    bool checkTestResults();

    TimeSeriesSet readTranslationOutput();
    void readTimeSeries(const std::string& name, TimeSeries& ts);

    // Config params
    QString ohq_file_path_;
    QString output_folder_;
    std::chrono::seconds read_interval_ = 30s; //reading time interval in seconds

    QTimer timer_;

    std::unique_ptr<TestTSBuilder> test_builder_;
    
    int      vars_ = 0;
    uint64_t current_pos_ = 0;
    uint64_t added_rows_  = 0;

    std::vector<std::string> names_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////

#endif // OHQTimeSeriesTranslator_H_B6055E29C4BC6BF8
