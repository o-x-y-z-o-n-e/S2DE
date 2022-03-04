#include "Texture.h"
#include "TextureManager.h"

#include <stddef.h>
#include <string>

namespace S2DE {

	Texture::Texture() {
		m_id = -1;
		m_width = 0;
		m_height = 0;
	}

	Texture* Texture::Load(std::string path) {
		Texture* texture = new Texture();

		texture->m_id = TextureManager::LoadTextureData(path);
		TextureManager::QueryTextureData(texture->m_id, NULL, &(texture->m_width), &(texture->m_height));

		return texture;
	}



	Texture* Texture::Create(std::string name, int w, int h) {
		Texture* texture = new Texture();

		texture->m_id = TextureManager::CreateTextureData(name, w, h);
		TextureManager::QueryTextureData(texture->m_id, NULL, &(texture->m_width), &(texture->m_height));

		return texture;
	}



	int Texture::GetID() { return m_id; }
	int Texture::GetWidth() { return m_width; }
	int Texture::GetHeight() { return m_height; }

}