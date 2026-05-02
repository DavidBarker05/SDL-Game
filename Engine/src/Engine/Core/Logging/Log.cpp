#include "Log.h"
#include <SDL3/SDL_log.h>
#include <iostream>
#include <iomanip>
#include <ctime> // Because displaying a decent time with chrono is a bitch
#include <cpptrace/basic.hpp>
#include "Math/Math.h"

#ifdef _MSC_VER
#pragma warning(disable : 4996) // Because MSVC won't let you compile if you use ctime stuff. Even tho this is a warning? Like wtf Microsoft?
#endif // _MSC_VER

#define DEFAULT_COLOUR "\33[0;0m"
#define GREEN "\33[0;92m"
#define YELLOW "\33[0;33m"
#define RED "\33[0;91m"
#define DEEPER_RED "\33[0;31m"

static INT8 s_LastLevel;
static INT8 s_CurrentLevel;

CSTRING FormatMessage(CSTRING format, va_list ap)
{
	// This is my understanding of how SDL does theirs, but like it's a lot shorter idk if I'm doing this in an unoptimised way but oh well
	char buffer[256];
	char* message = nullptr;
	INT32 len = vsnprintf(buffer, sizeof(buffer), format, ap);
	if (len < 0) return nullptr;
	message = new char[len + 1];
	if (sizeof(buffer) < len) vsnprintf(message, len + 1, format, ap);
	else std::memcpy(message, buffer, len);
	if (message[len] != '\0') message[len] = '\0';
	return const_cast<CSTRING>(message);
}

void LogMessage(LogLevel logLevel, CSTRING message)
{
	CSTRING type;
	CSTRING colour;
	bool bStackTrace = false;
	switch (logLevel)
	{
		case LogLevel::eTRACE:
			type = "TRACE";
			colour = DEFAULT_COLOUR;
			break;
		case LogLevel::eINFO:
			type = "INFO";
			colour = GREEN;
			break;
		case LogLevel::eWARN:
			type = "WARNING";
			colour = YELLOW;
			bStackTrace = true;
			break;
		case LogLevel::eERROR:
			type = "ERROR";
			colour = RED;
			bStackTrace = true;
			break;
		case LogLevel::eFATAL:
			type = "FATAL";
			colour = DEEPER_RED;
			bStackTrace = true;
			break;
		default:
			return;
	}
	std::time_t now = std::time(nullptr);
	std::tm* pLocalTime = std::localtime(&now);
	std::string stackMessage = bStackTrace ? "\n" : "";
	if (bStackTrace)
	{
		auto stackTrace = cpptrace::generate_trace(1); // 1 skips the current function
		for (auto it = stackTrace.cbegin(); it < stackTrace.cend(); ++it)
		{
			if (it->symbol.substr(0, strlen("LogOverrideFunction")) == "LogOverrideFunction") continue; // If rename the function don't forget to update string
			if (it->symbol.substr(0, strlen("SDL_")) == "SDL_") continue; // SDL better not change their naming convention
			stackMessage += it->filename.empty() ? it->symbol : it->filename;
			if (it->line.has_value()) stackMessage += " LINE " + std::to_string(it->line.value());
			break;
		}
	}
	std::cout << colour << type << ": [" << std::put_time(pLocalTime, "%H:%M:%S") << "] " << message << stackMessage << DEFAULT_COLOUR << "\n\n"; // Ouput to console
	// TODO: Output to a file
}

void LogOverrideFunction(void* userData, INT32 category, SDL_LogPriority priority, CSTRING message)
{
	LogLevel level;
	switch (priority)
	{
		case SDL_LOG_PRIORITY_VERBOSE:
			level = LogLevel::eTRACE;
			break;
		case SDL_LOG_PRIORITY_INFO:
			level = LogLevel::eINFO;
			break;
		case SDL_LOG_PRIORITY_WARN:
			level = LogLevel::eWARN;
			break;
		case SDL_LOG_PRIORITY_ERROR:
			level = LogLevel::eERROR;
			break;
		case SDL_LOG_PRIORITY_CRITICAL:
			level = LogLevel::eFATAL;
			break;
		default:
			return;
	}
	if (s_CurrentLevel < (INT8)level) return;
	LogMessage(level, message);
}

void Logger::Init()
{
#ifdef LOG_LEVEL_TRACE
	s_LastLevel = (INT8)LogLevel::eTRACE;	
	s_CurrentLevel = (INT8)LogLevel::eTRACE;
#elifdef LOG_LEVEL_INFO
	s_LastLevel = (INT8)LogLevel::eINFO;
	s_CurrentLevel = (INT8)LogLevel::eINFO;
#elifdef LOG_LEVEL_WARN
	s_LastLevel = (INT8)LogLevel::eWARN;
	s_CurrentLevel = (INT8)LogLevel::eWARN;
#elifdef LOG_LEVEL_ERROR
	s_LastLevel = (INT8)LogLevel::eERROR;
	s_CurrentLevel = (INT8)LogLevel::eERROR;
#elifdef LOG_LEVEL_FATAL
	s_LastLevel = (INT8)LogLevel::eFATAL;
	s_CurrentLevel = (INT8)LogLevel::eFATAL;
#elifdef LOG_LEVEL_NONE
	s_LastLevel = -1;	
	s_CurrentLevel = -1;
#else
	s_LastLevel = (INT8)LogLevel::eTRACE;
	s_CurrentLevel = (INT8)LogLevel::eTRACE;
#endif
	SDL_SetLogOutputFunction((SDL_LogOutputFunction) LogOverrideFunction, nullptr);
	LOG_INFO("Initialised the logging system");
}

void Logger::SetLevel(LogLevel level)
{
#ifndef LOCK_LOG_LEVEL
	s_LastLevel = s_CurrentLevel;
	s_CurrentLevel = (INT8)level;
#endif // !LOCK_LOG_LEVEL
}

void Logger::EnableLogging()
{
#ifndef LOCK_LOG_LEVEL
	s_CurrentLevel = Math::Max(0, s_LastLevel);
	s_LastLevel = Math::Max(0, s_LastLevel);
#endif // !LOCK_LOG_LEVEL
}

void Logger::DisableLogging()
{
#ifndef LOCK_LOG_LEVEL
	s_LastLevel = s_CurrentLevel;
	s_CurrentLevel = -1;
#endif // !LOCK_LOG_LEVEL
}

void Logger::Log(LogLevel logLevel, CSTRING format, ...)
{
	if (s_CurrentLevel < (INT8)logLevel) return;
	va_list ap;
	va_start(ap, format);
	CSTRING message = FormatMessage(format, ap);
	va_end(ap);
	if (!message) return;
	LogMessage(logLevel, message);
	delete[] message; // Delete message because it was allocated on the heap in FormatMessage
}
