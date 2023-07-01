#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_Logger;

std::shared_ptr<spdlog::logger>& Log::GetLogger()
{
	return s_Logger;
}

void Log::Init(spdlog::level::level_enum level)
{
	s_Logger = spdlog::stdout_color_mt("Logger:");
	s_Logger->set_level(level);
}

