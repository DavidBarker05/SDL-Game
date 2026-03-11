#ifndef LOGGER_H
#define LOGGER_H

#include "DataTypes.h"
#include <SDL3/SDL_log.h>

enum class LogLevel : UINT8
{
	eNONE,
	eFATAL,
	eERROR,
	eWARN,
	eINFO,
	eTRACE
};

#define SET_LOG_LEVEL(level) Logger::SetLevel(level)

#define LOG_TRACE(format, ...) SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, format, __VA_ARGS__)

#define LOG_INFO(format, ...) SDL_Log(format, __VA_ARGS__)

#define LOG_WARN(format, ...) SDL_LogWarn(SDL_LOG_CATEGORY_TEST, format "\n%s LINE %d", __VA_ARGS__, __FILE__, __LINE__)

#define LOG_ERROR(format, ...) SDL_LogError(SDL_LOG_CATEGORY_TEST, format "\n%s LINE %d", __VA_ARGS__, __FILE__, __LINE__)

#define LOG_FATAL(format, ...) SDL_LogCritical(SDL_LOG_CATEGORY_TEST, format "\n%s LINE %d", __VA_ARGS__, __FILE__, __LINE__)

// Basically a singleton to allow me to work with sdl logger and output to whatever file I want
namespace Logger
{
	extern void Init();
	
	extern void SetLevel(LogLevel level);

	extern void LogOverrideFunction(P_VOID userData, INT16 category, SDL_LogPriority priority, C_STRING message);
}
#endif // !LOGGER_H
