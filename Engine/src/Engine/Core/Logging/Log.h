#pragma once

#include "Types.h"

enum class LogLevel : INT8
{
	eFATAL,
	eERROR,
	eWARN,
	eINFO,
	eTRACE
};

#define SET_LOG_LEVEL(level) Logger::SetLevel(level)

#define LOG_TRACE(format, ...) Logger::Log(LogLevel::eTRACE, format, __VA_ARGS__)

#define LOG_INFO(format, ...) Logger::Log(LogLevel::eINFO, format, __VA_ARGS__)

#define LOG_WARN(format, ...) Logger::Log(LogLevel::eWARN, format, __VA_ARGS__)

#define LOG_ERROR(format, ...) Logger::Log(LogLevel::eERROR, format, __VA_ARGS__)

#define LOG_FATAL(format, ...) Logger::Log(LogLevel::eFATAL, format, __VA_ARGS__)

class Logger
{
public:
	static void Init();

	static void SetLevel(LogLevel level);

	static void EnableLogging();

	static void DisableLogging();

	static void Log(LogLevel logLevel, CSTRING format, ...);
};

