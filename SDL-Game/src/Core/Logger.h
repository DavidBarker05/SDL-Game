#ifndef LOGGER_H
#define LOGGER_H

#include "DataTypes.h"
#include <SDL2/SDL_log.h>

enum class LogLevel : UINT8
{
	eNONE,
	eFATAL,
	eERROR,
	eWARN,
	eINFO,
	eTRACE
};

#define SET_LOG_LEVEL(level) Logger::Get().SetLevel(level)

#define LOG_TRACE(format, ...) Logger::Get().LogTrace(format, __VA_ARGS__)

#define LOG_INFO(format, ...) Logger::Get().LogInfo(format, __VA_ARGS__)

#define LOG_WARN(format, ...) Logger::Get().LogWarn(format, __VA_ARGS__)

#define LOG_ERROR(format, ...) Logger::Get().LogError(format, __VA_ARGS__)

#define LOG_FATAL(format, ...) Logger::Get().LogFatal(format, __VA_ARGS__)

class Logger
{
public:
	static void Init()
	{
		s_Logger = { };
		s_Logger.m_CurrentLevel = LogLevel::eTRACE;
	}

	inline static Logger& Get() { return s_Logger; }

	template <typename... Args>
	void LogTrace(C_STRING format, Args... args)
	{
		if (m_CurrentLevel < LogLevel::eTRACE) return;
		SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, format, args...);
	}

	template <typename... Args>
	void LogInfo(C_STRING format, Args... args)
	{
		if (m_CurrentLevel < LogLevel::eINFO) return;
		SDL_Log(format, args...);
	}

	template <typename... Args>
	void LogWarn(C_STRING format, Args... args)
	{
		if (m_CurrentLevel < LogLevel::eWARN) return;
		SDL_LogWarn(SDL_LOG_CATEGORY_TEST, format, args...);
	}

	template <typename... Args>
	void LogError(C_STRING format, Args... args)
	{
		if (m_CurrentLevel < LogLevel::eERROR) return;
		SDL_LogError(SDL_LOG_CATEGORY_TEST, format, args...);
	}

	template <typename... Args>
	void LogFatal(C_STRING format, Args... args)
	{
		if (m_CurrentLevel < LogLevel::eFATAL) return;
		SDL_LogCritical(SDL_LOG_CATEGORY_TEST, format, args...);
	}

	void SetLevel(LogLevel level)
	{
		m_CurrentLevel = level;
	}

private:
	static Logger s_Logger;

	LogLevel m_CurrentLevel;
};
	
#endif // !LOGGER_H
