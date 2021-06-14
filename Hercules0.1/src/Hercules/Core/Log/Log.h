#pragma once

#include "Hercules/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hercules {
	
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
//pass multiple arguments into HC_CORE_ERROR and print them out with getcorelogger
#define HC_CORE_TRACE(...) ::Hercules::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HC_CORE_INFO(...) ::Hercules::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HC_CORE_STAT(...) ::Hercules::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HC_CORE_WARN(...) ::Hercules::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HC_CORE_ERROR(...) ::Hercules::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HC_CORE_FATAL(...) ::Hercules::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define HC_TRACE(...) ::Hercules::Log::GetClientLogger()->error(__VA_ARGS__)
#define HC_INFO(...) ::Hercules::Log::GetClientLogger()->info(__VA_ARGS__)
#define HC_STAT(...) ::Hercules::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HC_WARN(...) ::Hercules::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HC_ERROR(...) ::Hercules::Log::GetClientLogger()->error(__VA_ARGS__)
#define HC_FATAL(...) ::Hercules::Log::GetClientLogger()->critical(__VA_ARGS__)