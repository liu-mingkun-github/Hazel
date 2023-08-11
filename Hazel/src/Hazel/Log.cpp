#include "hzpch.h"
#include "Log.h"

// So normally, when creating a new file, normally we will create
// both .h and .cpp file, but it's important to design in advance
// which files should be the .h files that provide the library
// and which should provide the definition.

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;
	
	void Log::init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// Create a color multi-threaded logger
		s_coreLogger = spdlog::stdout_color_mt("HAZEL");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("APP");
		s_clientLogger->set_level(spdlog::level::trace);
	}
}
