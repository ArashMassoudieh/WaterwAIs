
#include "OHQTimeSeriesTranslator.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDir>

#include <thread>
#include <atomic>

namespace WaterwAIs {

using namespace std::chrono;

namespace {
    constexpr auto default_config_file    = "Config/TimeSeriesTranslatorConfig.json";
    constexpr auto default_test_cfg_file  = "Config/TimeSeriesTranslatorTestConfig.json";
    constexpr auto default_read_interval  = 30s;

    // Default test params
    constexpr auto default_write_interval = 2s;
    constexpr auto default_max_rows       = 30;
    constexpr auto default_num_of_series  = 5;


} // anonymous

//////////////////////////////////////////////////////////////////////////
// TestTSBuilder

class TestTSBuilder {
public:
    struct Params {
        QString  output_folder;
        QString  output_file;

        uint32_t row_increment = 5U;
        uint32_t max_rows = 100;

        int num_of_series = 5;

        std::chrono::seconds write_interval = 5s;

        uint32_t post_translate_counter = 3U;

        explicit operator bool() const {
            return !output_file.isEmpty() && !output_folder.isEmpty();
        }

        QString outputPath() const {
            return output_folder + QStringLiteral("/") + output_file;
        }
    };

    TestTSBuilder() {
        params_.output_file = "test_output.csv";
        params_.output_folder = "../Data";
    }

    ~TestTSBuilder() {
        stop();
    }

    void start() {
        if (running_)
            return;

        if (!params_) {
            qWarning() << "Invalid test parameters";
            return;
        }

        post_counter_ = 0;
        row_ = 0;
        running_ = true;
        run_thread_ = std::thread([this] { run(); });
    }

    void stop() {
        running_ = false;
        if (run_thread_.joinable())
            run_thread_.join();
    }

    void startPostCounting() { post_counter_++; }

    bool postCountingDone() const
        { return post_counter_ > params_.post_translate_counter; }

    Params& params() { return params_; }

private:
    using TimeSeriesSet = CTimeSeriesSet<double>;

    void run() {
        qDebug() << "Starting TS building test, output_path: " << 
            params_.outputPath();

        while (running_) {
            auto ts_set = TimeSeriesSet{params_.num_of_series};

            // Fill the series
            for (auto i = 0; i < ts_set.nvars; i++) {
                auto& ts = ts_set[i];

                ts.name = "Timeseries_" + std::to_string(i);
                ts_set.names[i] = ts.name;

                auto row = row_;

                for (auto j = 0U; j < params_.row_increment; j++) {
                    ts.append(40000.0 + row * 0.1 + j * 0.01, row + i + j);
                    row++;
                }
            }

            // Do writing            
            ts_set.writetofile(params_.outputPath().toStdString(), false, row_ != 0);

            row_ += params_.row_increment;
            qDebug() << "written " << row_ << " rows";

            if (row_ >= params_.max_rows) {
                running_ = false;
                break;
            }

            // Sleep until the next write
            std::this_thread::sleep_for(params_.write_interval);
        }

        qDebug() << "TS building test completed. Added " << row_ << " records";
    }
    
    Params           params_;
    std::atomic_bool running_;
    std::thread      run_thread_;
    uint32_t         row_ = 0;
    uint32_t         post_counter_ = 0U;
};


//////////////////////////////////////////////////////////////////////////
// OHQTimeSeriesTranslator

OHQTimeSeriesTranslator::OHQTimeSeriesTranslator(QObject* parent)
    : QObject(parent) {
}

OHQTimeSeriesTranslator::~OHQTimeSeriesTranslator() = default;

void OHQTimeSeriesTranslator::run(QStringView cfg_file) {
    auto config_file = cfg_file.empty() ? QString{default_config_file}
        : cfg_file.toString();

    if (!readConfig(config_file)) {
        qCritical() << "Failed to read configuration";
        return;
    }

    // Start translation
    runTranslation();
}

void OHQTimeSeriesTranslator::runTranslation() {
    // We start from the beginning of the file.
    current_pos_ = 0;
    vars_        = 0;
    added_rows_  = 0;

    names_.clear();

    translate();
    connect(&timer_, &QTimer::timeout, this, [this]() { translate(); });

    timer_.start(read_interval_);
}

bool OHQTimeSeriesTranslator::readConfig(const QString& config_file) {
    auto file = QFile{config_file};    

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Json file couldn't be opened/found";
        return false;
    }

    auto byte_array = file.readAll();
    file.close();

    auto parse_error = QJsonParseError{};    
    auto json_doc = QJsonDocument::fromJson(byte_array, &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at " << parse_error.offset
            << ":" << parse_error.errorString();
        return false;
    }

    auto json_obj = json_doc.object();

    ohq_file_path_ = json_obj["MainOHQoutput"].toString();
    output_folder_ = json_obj["TimeSeriesFolder"].toString();
    read_interval_ = seconds{json_obj["ReadInterval"].toInteger()};

    if (ohq_file_path_.isEmpty()) {
        qWarning() << "No OHQ output file to translate";
        return false;
    }

    if (output_folder_.isEmpty()) {
        qWarning() << "Output folder is not specified";
        return false;
    }

    QDir().mkpath(output_folder_);

    if (read_interval_ == 0s)
        read_interval_ = default_read_interval;

    return true;
}

void OHQTimeSeriesTranslator::translate() {
    qDebug() << "Translating ...";

    auto ohq_output = TimeSeriesSet{ohq_file_path_.toStdString(),
        true, current_pos_, names_};
    
    if (names_.empty()) {
        // Storing var names from the first read.
        for (auto& name : ohq_output.names)
            names_.emplace_back(name);
    }

    auto added = ohq_output.file_pos > current_pos_;

    if (added) {
        auto append = added_rows_ > 0;

        vars_ = ohq_output.nvars;
        current_pos_ = ohq_output.file_pos;
        added_rows_ += ohq_output.nvars > 0 ? ohq_output[0].tSize() : 0;

        for (int i = 0; i < ohq_output.nvars; i++) {
            ohq_output[i].writefile(output_folder_.toStdString() +
                "/" + ohq_output.names[i] + ".csv", append);
        }

        qDebug() << "processed " << added_rows_ << " records";
    }    

    if (test_builder_) {
        // Testing mode.

        auto& params = test_builder_->params();

        if (added_rows_ >= params.max_rows) {
            test_builder_->startPostCounting();

            if (test_builder_->postCountingDone()) {
                qDebug() << "All test records have been processed";
                qDebug() << "Added " << added_rows_ << " records";

                timer_.stop();

                auto exit_code = 0;

                // Now, we need to test if data in the OHQ output file path.
                // matches the TimeSeries CSV files.
                auto passed = checkTestResults();

                if (passed) {
                    qDebug() << "\nTranslation test PASSED";
                } else {
                    qDebug() << "\nTranslation test FAILED";
                    exit_code = 1;
                }

                QCoreApplication::exit(exit_code);
            }
        }
    }
}


bool OHQTimeSeriesTranslator::checkTestResults() {
    // Read TimeSeriesSet from OHQ output file.
    auto ohq_time_series = TimeSeriesSet{ohq_file_path_.toStdString(), true};
    auto& ohq_names = ohq_time_series.names;
    auto& ohq_btc   = ohq_time_series.BTC;

    // Read time series from CSV files created as translation result.
    auto csv_time_series = readTranslationOutput();
    auto& csv_names = csv_time_series.names;
    auto& csv_btc   = csv_time_series.BTC;

    if (ohq_names.size() != csv_names.size()) {
        qDebug() << "OHQ names size: " << ohq_names.size()
            << " doesn't match CSV time series name size: "
                << csv_names.size();
        return false;
    }

    for (auto i = 0; i < ohq_time_series.names.size(); i++) {
        if (ohq_names[i] != csv_names[i]) {
            qDebug() << "OHQ TS name: " << QUtf8StringView(ohq_names[i])
                << " not equal CSV TS name: " << QUtf8StringView(csv_names[i]);
            return false;
        }

        if (ohq_btc.size() != csv_btc.size()) {
            qDebug() << "Name: " << QUtf8StringView(ohq_names[i]) <<
                ", OHQ BTC size: " << ohq_btc.size() <<
                " not equal to CSV BTC size: " << csv_btc.size();
            return false;
        }

        for (auto j = 0; j < ohq_btc.size(); j++) {
            if (ohq_btc[j].GetT(j) != csv_btc[j].GetT(j) || 
                ohq_btc[j].GetC(j) != csv_btc[j].GetC(j)) {
                qDebug() << "Name: " << QUtf8StringView(ohq_names[i]) <<
                    ", values mismatch at " << j;
                return false;
            }
        }
    }
    return true;
}


void OHQTimeSeriesTranslator::runTest(QStringView test_cfg_file) {
    auto config_file = test_cfg_file.empty() ?
        QString{default_test_cfg_file} : test_cfg_file.toString();

    auto file = QFile{config_file};

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Json file couldn't be opened/found";
        return;
    }

    auto byte_array = file.readAll();
    file.close();

    auto parse_error = QJsonParseError{};
    auto json_doc = QJsonDocument::fromJson(byte_array, &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at " << parse_error.offset
            << ":" << parse_error.errorString();
        return;
    }

    auto json_obj = json_doc.object();

    ohq_file_path_ = json_obj["MainOHQoutput"].toString();
    output_folder_ = json_obj["TimeSeriesFolder"].toString();

    read_interval_ = seconds{json_obj["ReadInterval"]
        .toInteger(default_read_interval/1s)};

    if (ohq_file_path_.isEmpty()) {
        qWarning() << "No OHQ output file to translate";
        return;
    }

    if (output_folder_.isEmpty()) {
        qWarning() << "Output folder is not specified";
        return;
    }

    QDir().mkpath(output_folder_);
    
    auto write_data = json_obj["WriteData"].toBool(false);

    if (write_data) {
        // We need to generate test data.
        auto write_interval = seconds{json_obj["WriteInterval"]
            .toInteger(default_write_interval/1s)};

        auto max_rows = json_obj["MaxRows"].toInteger(default_max_rows);

        auto num_of_series
            = json_obj["NumOfSeries"].toInteger(default_num_of_series);

        test_builder_ = std::make_unique<TestTSBuilder>();

        auto& params = test_builder_->params();
        params.output_folder = output_folder_;

        params.num_of_series  = num_of_series;
        params.max_rows       = max_rows;
        params.write_interval = write_interval;

        test_builder_->start();
    }

    // Start translation
    runTranslation();
}


OHQTimeSeriesTranslator::TimeSeriesSet
OHQTimeSeriesTranslator::readTranslationOutput() {
    auto ts_set = TimeSeriesSet{static_cast<int>(names_.size())};

    // Setting names and filling Time series.
    for (auto i = 0; i < names_.size(); i++) {
        ts_set.names[i] = names_[i];
        
        // Reading TimeSeries from the CSV file.
        readTimeSeries(names_[i], ts_set.BTC[i]);
    }
    return ts_set;
}

void OHQTimeSeriesTranslator::readTimeSeries(const std::string& name,
    TimeSeries& ts) {

    auto file_path = output_folder_ + "/" + QString::fromUtf8(name.c_str()) +
        ".csv";

    auto file = QFile{file_path};

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "CSV file: " << file_path << " couldn't be opened/found";
        return;
    }

    // Parsing time series in CSV format
    auto stream = QTextStream{&file};
    auto line = QString{};

    while (stream.readLineInto(&line)) {
        auto parts = line.split(',', Qt::SkipEmptyParts);

        if (parts.size() == 2) {
            // We have both time and value
            auto time  = parts[0].trimmed().toDouble();
            auto value = parts[1].trimmed().toDouble();

            ts.append(time, value);
        }
    }
}


} // namespace WaterwAIs