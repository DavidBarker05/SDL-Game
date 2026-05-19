#pragma once

#include "Types.h"

// Different log levels/verbosities for the logging system
enum class LogLevel : INT8
{
	eFATAL,
	eERROR,
	eWARN,
	eINFO,
	eTRACE
};

// Set the current log level for the logger. The levels from highest to lowest
// verbosity are: eTRACE, eINFO, eWARN, eERROR and eFATAL.
#define SET_LOG_LEVEL(level) Logger::SetLevel(level)

// Enable logging
#define LOG_ENABLE() Logger::EnableLogging()

// Disable logging
#define LOG_DISABLE() Logger::DisableLogging()

// Log a message at the eTRACE level. If level is set to eINFO, eWARN, eERROR or
// eFATAL or logging is disabled then this log will be ignored
#define LOG_TRACE(format, ...) Logger::Log(LogLevel::eTRACE, format, __VA_ARGS__)

// Log a message at the eINFO level. If level is set to eWARN, eERROR or eFATAL
// or logging is disabled then this log will be ignored
#define LOG_INFO(format, ...) Logger::Log(LogLevel::eINFO, format, __VA_ARGS__)

// Log a message at the eWARN level. If level is set to eERROR or eFATAL or
// disabled then this log will be ignored
#define LOG_WARN(format, ...) Logger::Log(LogLevel::eWARN, format, __VA_ARGS__)

// Log a message at the eERROR level. If the level is set to eFATAL or
// logging is disabled then this message will be ignored
#define LOG_ERROR(format, ...) Logger::Log(LogLevel::eERROR, format, __VA_ARGS__)

// Log a message at the eFATAL level. If logging is disabled then this message
// will be ignored
#define LOG_FATAL(format, ...) Logger::Log(LogLevel::eFATAL, format, __VA_ARGS__)

class Logger
{
public:
	static bool IsInitialized();
	// Initialise the logging system
	static void Init();

	// Set the current log level for the logger. The levels from highest to lowest
	// verbosity are: eTRACE, eINFO, eWARN, eERROR and eFATAL.
	static void SetLevel(LogLevel level);

	// Enable logging
	static void EnableLogging();

	// Disable logging
	static void DisableLogging();

	// Log a message
	static void Log(LogLevel logLevel, CSTRING format, ...);
};
