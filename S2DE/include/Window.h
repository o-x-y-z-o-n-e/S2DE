#pragma once

#include <SDL.h>
#include <string>

#include "Texture.h"

namespace S2DE {

    class Window {
	public:
		static int Init();
		static void Clear();
		static void Update();
		static void Close();
		static void ApplyTexture(Texture* texture, int x, int y);
		static Texture* LoadTexture(std::string path);
		static SDL_Renderer* GetRenderer();

	private:
		Window() {}

	};
}
