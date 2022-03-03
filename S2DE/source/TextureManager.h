#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Core.h"
#include "Texture.h"
#include <string>

#define TEXTURE_TABLE_SIZE 1000


namespace S2DE {

	namespace TextureManager {

		void InitTextureManager();
		int LoadTextureData(std::string path);
		void FreeTextureData(int id);
		SDL_Texture* GetTextureData(int id);

	}
}

#endif