#ifndef WINDOW_H
#define WINDOW_H

#include "Core.h"
#include "Texture.h"

namespace S2DE {

	namespace Window {

		int Init();
		void Clear();
		void Update();
		void Close();
		void ApplyTexture(Texture* texture, int x, int y);
		SDL_Renderer* GetRenderer();

	}

}

#endif