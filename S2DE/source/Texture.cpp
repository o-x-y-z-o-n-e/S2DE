#include "Texture.h"
#include "TextureManager.h"

#include <stddef.h>
#include <string>

namespace S2DE {

	Texture::Texture() {
		m_id = 0;
		m_width = 0;
		m_height = 0;
	}

	Texture::~Texture() {
		
	}

	bool Texture::Load(std::string path) {
		m_id = LoadTextureData(path.c_str());
		return true;
	}

	int Texture::GetID() { return m_id; }
	int Texture::GetWidth() { return m_width; }
	int Texture::GetHeight() { return m_height; }

}