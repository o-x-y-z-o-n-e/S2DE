#include "Console.h"
#include "Application.h"
#include "Global.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "spdlog/sinks/stdout_color_sinks.h"

namespace S2DE {

	bool Console::m_hasInit;
	std::shared_ptr<spdlog::logger> Console::s_mainLogger;
	std::shared_ptr<spdlog::logger> Console::s_coreLogger;

	void Console::Init() {
		if (m_hasInit)
			return;

		spdlog::set_pattern("[%n][%l] %v");

		s_coreLogger = spdlog::stdout_color_mt("S2DE");
		s_coreLogger->set_level(spdlog::level::info);

		s_mainLogger = spdlog::stdout_color_mt("GAME");
		s_mainLogger->set_level(spdlog::level::info);

		m_hasInit = true;
	}


    void Log(const char* format, ...) {
		va_list args;
		va_start(args, format);

		Console::GetMainLogger()->info(format, args);
		va_end(args);
    }

    void LogWarning(const char* format, ...) {
		va_list args;
		va_start(args, format);

		Console::GetMainLogger()->error(format, args);
		va_end(args);
    }

    void LogError(const char* format, ...) {
		va_list args;
		va_start(args, format);

		Console::GetMainLogger()->error(format, args);
		va_end(args);
    }



    void LogCore(const char* format, ...) {
		va_list args;
		va_start(args, format);
		
		Console::GetCoreLogger()->info(format, args);
		va_end(args);
    }


    void LogCoreWarning(const char* format, ...) {
		va_list args;
		va_start(args, format);

		Console::GetCoreLogger()->error(format, args);
		va_end(args);
    }

    void LogCoreError(const char* format, ...) {
		va_list args;
		va_start(args, format);

		Console::GetCoreLogger()->error(format, args);
		va_end(args);
    }

}