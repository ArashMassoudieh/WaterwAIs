#
# This folder contains examples of main and test configuration files
# for the TimeSeriesTranslator application.
#

TimeSeriesTranslatorConfig.json
	- Example of the main configuration file.
	  This file specifies parameters of translation from OHQ output
	  format into WaterwAI time series CSV files.

TimeSeriesTranslatorTestConfig.json
	- Example of the test configuration file allowing to run the
	  TimeSeriesTranslator application in the test mode.
	  The test mode allows to dynamically generate some test OHQ
	  output file, translate it into WaterwAI CSV file format and
	  verify that translation was done correctly without data loss.