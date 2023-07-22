#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace hazel {

	class HAZEL_API Log {
		
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;

	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {
			return s_coreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& getClientLogger() {
			return s_clientLogger;
		}
	};
}

// Core log macros
#define HZ_CORE_TRACE(...)	::hazel::Log::getCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INO(...)	::hazel::Log::getCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)	::hazel::Log::getCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)	::hazel::Log::getCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)	::hazel::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...)	::hazel::Log::getClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)	::hazel::Log::getClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)	::hazel::Log::getClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)	::hazel::Log::getClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...)	::hazel::Log::getClientLogger()->fatal(__VA_ARGS__)

