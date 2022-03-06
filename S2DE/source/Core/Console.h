#ifndef S2DE_CONSOLE_H
#define S2DE_CONSOLE_H

#include "spdlog/spdlog.h"

#define CONSOLE_BUFFER_SIZE 512

namespace S2DE {

	class Console {

	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetMainLogger() { return s_mainLogger; }
		inline static char* GetBuffer() { return buffer; }

	private:
		static bool m_hasInit;
		static std::shared_ptr<spdlog::logger> s_mainLogger;
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static char buffer[];

	};

}

#endif