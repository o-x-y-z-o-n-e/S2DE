#include "Application.h"
#include "Console.h"

#include <stdio.h>
#include <stdbool.h>

namespace S2DE {


	void Console::Init() {
		if (m_hasInit)
			return;

		m_hasInit = true;
	}


    void Log(const char* message) {
        printf("%s\n", message);
    }

    void LogWarning(const char* message) {
        printf("[WARNING] %s\n", message);
    }

    void LogError(const char* message) {
        printf("[ERROR] %s\n", message);
    }

    void LogCore(const char* message) {
        printf("[S2DE] %s\n", message);
    }

    void LogCoreWarning(const char* message) {
        printf("[S2DE][WARNING] %s\n", message);
    }

    void LogCoreError(const char* message) {
        printf("[S2DE][ERROR] %s\n", message);
    }

}