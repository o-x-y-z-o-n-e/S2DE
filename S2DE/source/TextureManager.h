#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#define TEXTURE_TABLE_SIZE 1000

#include <string.h>
#include "Texture.h"
#include "SDL2/SDL.h"

namespace S2DE {

	namespace TextureManager {

		void InitTextureManager();
		int LoadTextureData(const char* path);
		void FreeTextureData(int id);
		SDL_Texture* GetTextureData(int id);
		SDL_Texture* LoadBMP(const char* path);

	}
}

#endif