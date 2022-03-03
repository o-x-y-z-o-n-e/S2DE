#include "Texture.h"
#include "TextureManager.h"
#include "Window.h"

#include <stddef.h>
#include <string>

namespace S2DE {

	Texture::Texture() {
		m_id = -1;
		m_width = 0;
		m_height = 0;
	}

	bool Texture::Load(std::string path) {
		m_id = TextureManager::LoadTextureData(path.c_str());
		SDL_Texture* texData = (SDL_Texture*)TextureManager::GetTextureData(m_id);

		SDL_QueryTexture(texData, NULL, NULL, &m_width, &m_height);

		return true;
	}

	int Texture::GetID() { return m_id; }
	int Texture::GetWidth() { return m_width; }
	int Texture::GetHeight() { return m_height; }

}