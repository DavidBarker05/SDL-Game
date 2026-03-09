#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <ctime>

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif // _MSC_VER

#define DEFAULT_COLOUR "\33[0;0m"
#define GREEN "\33[0;92m"
#define YELLOW "\33[0;33m"
#define RED "\33[0;91m"
#define INTENSE_RED "\33[0;31m"

static LogLevel currentLevel;

void Logger::Init()
{
#ifdef LOG_LEVEL_TRACE
	currentLevel = LogLevel::eTRACE;
#elifdef LOG_LEVEL_INFO
	currentLevel = LogLevel::eINFO;
#elifdef LOG_LEVEL_WARN
	currentLevel = LogLevel::eWARN;
#elifdef LOG_LEVEL_ERROR
	currentLevel = LogLevel::eERROR;
#elifdef LOG_LEVEL_FATAL
	currentLevel = LogLevel::eFATAL;
#elifdef LOG_LEVEL_NONE
	currentLevel = LogLevel::eNONE;
#else
	currentLevel = LogLevel::eTRACE;
#endif
	SDL_LogSetOutputFunction((SDL_LogOutputFunction) LogOverrideFunction, (P_VOID) 0);
	LOG_INFO("Initialised the logging system");
}

void Logger::SetLevel(LogLevel level)
{
#ifndef LOCK_LOG_LEVEL
	currentLevel = level;
#endif // !LOCK_LOG_LEVEL
}

void Logger::LogOverrideFunction(P_VOID userData, INT16 category, SDL_LogPriority priority, C_STRING message)
{
#if defined(_CONSOLE) || defined(_FILE)
	C_STRING type;
	C_STRING colour;
	switch (priority)
	{
		case SDL_LOG_PRIORITY_VERBOSE:
			if (currentLevel < LogLevel::eTRACE) return;
			type = "TRACE";
			colour = DEFAULT_COLOUR;
			break;
		case SDL_LOG_PRIORITY_INFO:
			if (currentLevel < LogLevel::eINFO) return;
			type = "INFO";
			colour = GREEN;
			break;
		case SDL_LOG_PRIORITY_WARN:
			if (currentLevel < LogLevel::eWARN) return;
			type = "WARNING";
			colour = YELLOW;
			break;
		case SDL_LOG_PRIORITY_ERROR:
			if (currentLevel < LogLevel::eERROR) return;
			type = "ERROR";
			colour = RED;
			break;
		case SDL_LOG_PRIORITY_CRITICAL:
			if (currentLevel < LogLevel::eFATAL) return;
			type = "FATAL";
			colour = INTENSE_RED;
			break;
		default:
			return;
	}

	std::time_t now = std::time(nullptr);
	std::tm* localTime = std::localtime(&now);

#ifdef _CONSOLE
	std::cout << colour << type << ": [" << std::put_time(localTime, "%H:%M:%S") << "] " << message << DEFAULT_COLOUR << "\n\n"; // Ouput to console
#endif // _CONSOLE

#ifdef _FILE
	// Output to file
#endif // _FILE

#endif // defined(_CONSOLE) || defined(_FILE)
}
