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

		static void SetViewPosition(float x, float y);
		static void GetViewPosition(float* x, float* y);
		static void SetViewSize(int w, int h);
		static void GetViewSize(int* w, int* h);

		static void SetTitle(const char* title);

	private:
		static bool m_hasInit;
		static SDL_Window* m_window;
		static SDL_Renderer* m_renderer;
		static vec2i m_windowSize;
		static vec2i m_viewSize;
		static vec2i m_viewOffset;
		static vec2f m_viewPosition;
		

	};

}

#endif