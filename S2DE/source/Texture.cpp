#include "Texture.h"
#include "internal/Window.h"

#include <SDL_image.h>

namespace S2DE {

	Texture::Texture() {
		m_tex = NULL;
		m_width = 0;
		m_height = 0;
	}

	Texture::~Texture() {
		Free();
	}

	bool Texture::Load(std::string path) {
		Free();

		SDL_Texture* texture = NULL;

		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) {
			printf("[S2DE] Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
			texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), loadedSurface);
			if (texture == NULL) {
				printf("[S2DE] Unable to load texture %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			} else {
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}

			SDL_FreeSurface(loadedSurface);
		}

		m_tex = texture;
		return m_tex != NULL;
	}

	void Texture::Free() {
		m_width = 0;
		m_height = 0;
		if (m_tex == NULL) return;
		SDL_DestroyTexture(m_tex);
		m_tex = NULL;
	}

	int Texture::GetWidth() { return m_width; }
	int Texture::GetHeight() { return m_height; }
	SDL_Texture* Texture::GetSDL() { return m_tex; }

}