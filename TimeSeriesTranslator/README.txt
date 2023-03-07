#
# OHQ TimeSeries Translator
#

This application provides translation from OHQ time series output
format into WaterwAIs time series CSV format.

It has two modes:
- Main mode
	Takes OHQ time series output file which can be updated dynamically
	and converts it into WaterwAIs time series CSV format.
	
- Test mode
	Dynamically generates test OHQ time series output file, 
	converts it into WaterwAIs time series CSV format and verifies that
	translation was done correctly without data loss.
	
Both modes have their own configuration files (see examples in /Config folder).
which can be provided via command line.

By default application looks into /Config folder format and searches for
TimeSeriesTranslatorConfig.json (Main mode) or 
TimeSeriesTranslatorTestConfig.json (Test mode)

Usage:

TimeSeriesTranslator[.exe] [options]

Options:
  -?, -h, --help               Displays help on commandline options.
  --help-all                   Displays help including Qt specific options.
  -v, --version                Displays version information.
  -t, --test                   Run in the test mode.
  -s, --tst_cfg <test_config>  Test Configuration file.
  -c, --cfg <config>           Configuration file.
