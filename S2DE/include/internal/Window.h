#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>
#include "Texture.h"

namespace S2DE {

	namespace Window {

		int Init();
		void Clear();
		void Update();
		void Close();
		void ApplyTexture(Texture* texture, int x, int y);
		Texture* LoadTexture(std::string path);
		SDL_Renderer* GetRenderer();

	}

}

#endif