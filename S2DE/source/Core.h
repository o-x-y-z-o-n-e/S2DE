#ifndef S2DE_CORE_H
#define S2DE_CORE_H

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#endif

namespace S2DE::Console {

    void LogCore(const char* message);
    void LogCoreWarning(const char* message);
    void LogCoreError(const char* message);

}

#endif