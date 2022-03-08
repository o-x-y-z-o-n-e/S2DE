#include "Global.h"
#include "Window.h"
#include "TextureManager.h"
#include "Types.h"

#include <iostream>
#include <stddef.h>

#define DEFAULT_VIEW {320,200}
#define DEFAULT_SCALE 4

namespace S2DE {

	const char* TITLE = "S2DE";

	bool Window::m_hasInit;
	SDL_Window* Window::m_window;
	SDL_Renderer* Window::m_renderer;
	vec2i Window::m_windowSize;
	vec2i Window::m_viewSize;
	vec2i Window::m_viewOffset;
	vec2f Window::m_viewPosition;


	SDL_Renderer* Window::GetRenderer() { return m_renderer; }


	int Window::Init() {
		if (m_hasInit) return 0;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("[S2DE] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 0;
		}

		m_viewSize = DEFAULT_VIEW;
		m_viewOffset.x = m_viewSize.x / 2;
		m_viewOffset.y = m_viewSize.y / 2;
		m_windowSize.x = m_viewSize.x * DEFAULT_SCALE;
		m_windowSize.y = m_viewSize.y * DEFAULT_SCALE;

		m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowSize.x, m_windowSize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (m_window == NULL) {
			printf("[S2DE] Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return 0;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (m_renderer == NULL) {
			printf("[S2DE] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return 0;
		}

		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0x00);
		SDL_RenderSetLogicalSize(m_renderer, m_viewSize.x, m_viewSize.y);

		m_hasInit = true;
		return 1;
	}


	void Window::Clear() {
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(m_renderer);
	}


	void Window::Update() {
		SDL_RenderPresent(m_renderer);
	}


	void Window::Close() {
		if (Core::IsRunning()) {
			Core::Close();
			return;
		}

		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);

		m_window = NULL;
		m_renderer = NULL;

		SDL_Quit();
	}


	void Window::ApplyTexture(Texture& texture, int x, int y) {
		SDL_Rect rect = { (m_viewOffset.x - (int)m_viewPosition.x) + x, (m_viewOffset.y + (int)m_viewPosition.y) - y, texture.GetWidth(), texture.GetHeight() };
		SDL_Texture* tex = (SDL_Texture*)TextureManager::GetTextureData(texture.GetID());

		SDL_RenderCopy(m_renderer, tex, NULL, &rect);
	}


	void Window::SetTitle(const char* title) { SDL_SetWindowTitle(m_window, title); }


	void Window::HandleWindowEvent(SDL_WindowEvent& e) {
		switch (e.event) {
			case SDL_WINDOWEVENT_RESIZED: {
				LogCore("Resized Window to %dx%d", e.data1, e.data2);
				break;
			}
		}
	}


	void Window::SetViewPosition(float x, float y) {
		m_viewPosition.x = x;
		m_viewPosition.y = y;
	}

	void Window::GetViewPosition(float* x, float* y) {
		if(x != NULL) *x = m_viewPosition.x;
		if(y != NULL) *y = m_viewPosition.y;
	}

	void Window::SetViewSize(int w, int h) {
		if (w < 0) w *= -1;
		if (h < 0) h *= -1;

		m_viewSize.x = w;
		m_viewSize.y = h;
		m_viewOffset.x = m_viewSize.x / 2;
		m_viewOffset.y = m_viewSize.y / 2;

		SDL_RenderSetLogicalSize(m_renderer, m_viewSize.x, m_viewSize.y);
	}

	void Window::GetViewSize(int* w, int* h) {
		if (w != NULL) *w = m_viewSize.x;
		if (h != NULL) *h = m_viewSize.y;
	}


	//--------------------------------


	void SetTitle(const char* title) { Window::SetTitle(title); }


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