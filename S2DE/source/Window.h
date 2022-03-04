#ifndef WINDOW_H
#define WINDOW_H

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#endif

#include "Types.h"
#include "Core.h"
#include "Texture.h"

namespace S2DE {

	class Window {

	public:
		static int Init();
		static void Clear();
		static void Update();
		static void Close();
		static void ApplyTexture(Texture* texture, int x, int y);
		static SDL_Renderer* GetRenderer();
		static void HandleWindowEvent(SDL_WindowEvent* e);

		static void SetPosition(float x, float y);
		static void SetPosition(vec2f position);
		static void GetPosition(float* x, float* y);
		static vec2f GetPosition();

	private:
		static bool m_hasInit;
		static SDL_Window* m_window;
		static SDL_Renderer* m_renderer;
		static int m_width;
		static int m_height;
		static vec2f m_position;

	};

}

#endif