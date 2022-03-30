#include "Global.h"
#include "Window.h"
#include "TextureManager.h"
#include "Types.h"
#include "Application.h"

#include <iostream>
#include <stddef.h>

#define DEFAULT_VIEW {320,200}
#define DEFAULT_SCALE 4

namespace S2DE {

	const char* TITLE = "S2DE";

	bool Window::s_hasInit;
	SDL_Window* Window::s_window;
	SDL_Renderer* Window::s_renderer;
	vec2i Window::s_windowSize;
	vec2i Window::s_viewSize;
	vec2i Window::s_viewOffset;
	vec2f Window::s_viewPosition;


	SDL_Renderer* Window::GetRenderer() { return s_renderer; }


	int Window::Init() {
		if (s_hasInit) return 0;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("[S2DE] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 0;
		}

		s_viewSize = DEFAULT_VIEW;
		s_viewOffset.x = s_viewSize.x / 2;
		s_viewOffset.y = s_viewSize.y / 2;
		s_windowSize.x = s_viewSize.x * DEFAULT_SCALE;
		s_windowSize.y = s_viewSize.y * DEFAULT_SCALE;

		s_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_windowSize.x, s_windowSize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (s_window == NULL) {
			printf("[S2DE] Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return 0;
		}

		s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED);
		if (s_renderer == NULL) {
			printf("[S2DE] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return 0;
		}

		SDL_SetRenderDrawColor(s_renderer, 0xFF, 0xFF, 0xFF, 0x00);
		SDL_RenderSetLogicalSize(s_renderer, s_viewSize.x, s_viewSize.y);

		s_hasInit = true;
		return 1;
	}


	void Window::Clear() {
		SDL_SetRenderDrawColor(s_renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(s_renderer);
	}


	void Window::Update() {
		SDL_RenderPresent(s_renderer);
	}


	void Window::Close() {
		if (Core::IsRunning()) {
			Core::Close();
			return;
		}

		SDL_DestroyRenderer(s_renderer);
		SDL_DestroyWindow(s_window);

		s_window = NULL;
		s_renderer = NULL;

		SDL_Quit();
	}


	void Window::ApplyTexture(Texture& texture, int x, int y) {
		SDL_Rect rect = { (s_viewOffset.x - (int)s_viewPosition.x) + x, (s_viewOffset.y + (int)s_viewPosition.y) - y - texture.GetHeight(), texture.GetWidth(), texture.GetHeight() };
		SDL_Texture* tex = (SDL_Texture*)TextureManager::GetTextureData(texture.GetID());

		SDL_RenderCopy(s_renderer, tex, NULL, &rect);
	}


	void Window::SetTitle(const char* title) { SDL_SetWindowTitle(s_window, title); }


	void Window::HandleWindowEvent(SDL_WindowEvent& e) {
		switch (e.event) {
			case SDL_WINDOWEVENT_RESIZED: {
				LogCore("Resized Window to %dx%d", e.data1, e.data2);
				break;
			}
		}
	}


	void Window::SetViewPosition(float x, float y) {
		s_viewPosition.x = x;
		s_viewPosition.y = y;
	}

	void Window::GetViewPosition(float* x, float* y) {
		if(x != NULL) *x = s_viewPosition.x;
		if(y != NULL) *y = s_viewPosition.y;
	}

	void Window::SetViewSize(int w, int h) {
		if (w < 0) w *= -1;
		if (h < 0) h *= -1;

		s_viewSize.x = w;
		s_viewSize.y = h;
		s_viewOffset.x = s_viewSize.x / 2;
		s_viewOffset.y = s_viewSize.y / 2;

		SDL_RenderSetLogicalSize(s_renderer, s_viewSize.x, s_viewSize.y);
	}

	void Window::GetViewSize(int* w, int* h) {
		if (w != NULL) *w = s_viewSize.x;
		if (h != NULL) *h = s_viewSize.y;
	}


	void Window::SetMode(int mode) {
		Uint32 flags = 0;

		switch (mode) {
		case S2DE_WINDOWED: 
			flags = 0;
			break;
		case S2DE_FULLSCREEN:
			flags = SDL_WINDOW_FULLSCREEN;
			break;
		case S2DE_BORDERLESS:
			flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		SDL_SetWindowFullscreen(s_window, flags);
	}


	void Window::SetRefreshRate(int fps) {
		
	}


	//--------------------------------


	void SetTitle(const char* title) { Window::SetTitle(title); }
	void SetWindowMode(int mode) { Window::SetMode(mode); }


	namespace Camera {

		void SetPosition(float x, float y) { Window::SetViewPosition(x, y); }
		void SetPosition(vec2f position) { Window::SetViewPosition(position.x, position.y); }
		void GetPosition(float* x, float* y) { Window::GetViewPosition(x, y); }
		vec2f GetPosition() {
			float x, y = 0;
			Window::GetViewPosition(&x, &y);
			return { x, y };
		}


		void SetSize(int w, int h) { Window::SetViewSize(w, h); }
		void SetSize(vec2i d) { Window::SetViewSize(d.x, d.y); }
		void GetSize(int* w, int* h) { Window::GetViewSize(w, h); }
		vec2i GetSize() {
			int w, h = 0;
			Window::GetViewSize(&w, &h);
			return { w, h };
		}

	}

}