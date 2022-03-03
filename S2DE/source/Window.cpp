#include "S2DE.h"
#include "Window.h"
#include "TextureManager.h"
#include "Types.h"

#include <iostream>
#include <stddef.h>

namespace S2DE {


	const char* TITLE = "S2DE";

	const int CAMERA_WIDTH = 320;
	const int CAMERA_HEIGHT = 200;
	const int CAMERA_X_OFFSET = CAMERA_WIDTH / 2;
	const int CAMERA_Y_OFFSET = CAMERA_HEIGHT / 2;

	bool Window::m_hasInit;
	SDL_Window* Window::m_window;
	SDL_Renderer* Window::m_renderer;
	int Window::m_width;
	int Window::m_height;
	vec2f Window::m_position;


	SDL_Renderer* Window::GetRenderer() {
		return m_renderer;
	}


	int Window::Init() {
		if (m_hasInit) return 0;

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			printf("[S2DE] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 0;
		}

		m_width = CAMERA_WIDTH * 4;
		m_height = CAMERA_HEIGHT * 4;

		m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
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
		SDL_RenderSetLogicalSize(m_renderer, CAMERA_WIDTH, CAMERA_HEIGHT);

		m_position = { 0, 0 };

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


	void Window::ApplyTexture(Texture* texture, int x, int y) {
		SDL_Rect rect = { (CAMERA_X_OFFSET - (int)m_position.x) + x, (CAMERA_Y_OFFSET + (int)m_position.y) + y, texture->GetWidth(), texture->GetHeight() };
		SDL_Texture* tex = (SDL_Texture*)TextureManager::GetTextureData(texture->GetID());

		SDL_RenderCopy(m_renderer, tex, NULL, &rect);
	}


	void Window::SetPosition(float x, float y) {
		m_position.x = x;
		m_position.y = y;
	}
	void Window::GetPosition(float* x, float* y) {
		if(x != NULL) *x = m_position.x;
		if(y != NULL) *y = m_position.y;
	}

	void Window::SetPosition(vec2f position) { m_position = position; }
	vec2f Window::GetPosition() { return m_position; }



	namespace Camera {

		void SetPosition(float x, float y) { Window::SetPosition(x, y); }
		void SetPosition(vec2f position) { Window::SetPosition(position); }
		void GetPosition(float* x, float* y) { Window::GetPosition(x, y); }
		vec2f GetPosition() { return Window::GetPosition(); }

	}

}