#include "Sprite.h"
#include "Types.h"
#include "Texture.h"
#include "Object.h"
#include "Window.h"

#include <stddef.h>

namespace S2DE {

	Sprite::~Sprite() {
		//CHANGE (IMPLEMENT TEXTURE MANAGER)
		/*
		if (m_texture != NULL) {
			m_texture->Free();
			m_texture = NULL;
		}
		*/
	}

	void Sprite::Init() {

	}

	void Sprite::Start() {

	}

	void Sprite::LateUpdate(float delta) {
		if (m_texture != NULL) {
			vec2f position = GetObject()->GetPosition();
			if (Centered) {
				position.x -= m_texture->GetWidth() / 2;
				position.y -= m_texture->GetHeight() / 2;
			}

			Window::ApplyTexture(m_texture, (int)position.x, (int)position.y);
		}
	}

	void Sprite::SetTexture(Texture* texture) {
		m_texture = texture;
	}

}