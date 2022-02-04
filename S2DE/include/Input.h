#pragma once

#include <string>
#include <SDL.h>

namespace S2DE {

    struct InputBinding {
    public:
        std::string name;
        SDL_Keycode binding;
        bool press;
        bool release;

    public:
        InputBinding(std::string name, SDL_Keycode binding) {
            this->name = name;
            this->binding = binding;
            press = false;
            release = true;
        }
    };


    class Input {

    public:
        static void AddBinding(std::string name, SDL_Keycode binding);
        static void SetPress(SDL_Keycode key);
        static void Flush();
        static void CheckRelease();
        static bool GetPress(std::string name);
        static bool GetClick(std::string name);

    };

}
