#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

class Log
{
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
public:
	static std::shared_ptr<spdlog::logger>& GetLogger();
	static void Init(spdlog::level::level_enum level);
};


#define LOG_INFO(...)		Log::GetLogger()->info(__VA_ARGS__)
#define LOG_ERROR(...)		Log::GetLogger()->error(__VA_ARGS__)
#define LOG_WARNING(...)	Log::GetLogger()->warn(__VA_ARGS__)