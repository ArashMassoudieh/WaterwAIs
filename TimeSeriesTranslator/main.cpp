
#include <QCoreApplication>
#include <QTimer>
#include <QCommandLineParser>

#include "OHQTimeSeriesTranslator.h"

using namespace WaterwAIs;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("OHQTimeSeriesTranslator");
    QCoreApplication::setApplicationVersion("1.0");

    auto parser = QCommandLineParser{};
    parser.setApplicationDescription("OHQ TimeSeries Translator");
    parser.addHelpOption();
    parser.addVersionOption();
    
    // A boolean "test" option with multiple names (-t, --test)
    auto test_option = QCommandLineOption({{"t", "test"},
        "Run in the test mode."});

    parser.addOption(test_option);

    // The "tst_cfg" (-s, --tst_cfg) option allowing to specify the test
    // config file.
    auto test_cfg_option = QCommandLineOption({{"s","tst_cfg"}, 
        "Test Configuration file.", "test_config"});

    parser.addOption(test_cfg_option);

    // The "cfg" (-c, --cfg) option allowing to specify the Translator
    // config file.
    auto cfg_option = QCommandLineOption({{"c","cfg"},
        "Configuration file.", "config"});

    parser.addOption(cfg_option);

    // Process the actual command line arguments given by the user
    parser.process(app);
    
    auto cfg_file      = parser.value(cfg_option);
    auto test_mode     = parser.isSet(test_option);
    auto test_cfg_file = parser.value(test_cfg_option);

    auto translator = OHQTimeSeriesTranslator{};

    if (!test_mode) {
        // Run in the Main mode
        translator.run(cfg_file);

    } else {
        // Run in the Test mode
        translator.runTest(test_cfg_file);
    }

    return app.exec();
}
