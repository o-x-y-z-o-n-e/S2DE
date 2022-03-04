#include "Console.h"
#include "Application.h"
#include "Global.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "spdlog/sinks/stdout_color_sinks.h"

#define S2DE_LOG(fmt, log, lvl) va_list args;va_start(args, fmt);vsprintf(Console::GetBuffer(), fmt, args);log->lvl(Console::GetBuffer());va_end(args);

namespace S2DE {

	bool Console::m_hasInit;
	std::shared_ptr<spdlog::logger> Console::s_mainLogger;
	std::shared_ptr<spdlog::logger> Console::s_coreLogger;
	char Console::buffer[CONSOLE_BUFFER_SIZE];

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
		S2DE_LOG(format, Console::GetMainLogger(), info);
    }

    void LogWarning(const char* format, ...) {
		S2DE_LOG(format, Console::GetMainLogger(), error);
    }

    void LogError(const char* format, ...) {
		S2DE_LOG(format, Console::GetMainLogger(), error);
    }

    void LogCore(const char* format, ...) {
		S2DE_LOG(format, Console::GetCoreLogger(), info);
    }

    void LogCoreWarning(const char* format, ...) {
		S2DE_LOG(format, Console::GetCoreLogger(), error);
    }

    void LogCoreError(const char* format, ...) {
		S2DE_LOG(format, Console::GetCoreLogger(), error);
    }

}