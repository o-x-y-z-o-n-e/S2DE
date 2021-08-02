#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace S2DE {
    class Texture {
	public:
		Texture();
		~Texture();
		bool Load(std::string path);
		void Free();
		int GetWidth();
		int GetHeight();
		SDL_Texture* GetSDL();

	private:
		SDL_Texture* sdl_texture;
		int width;
		int height;
	};
}
