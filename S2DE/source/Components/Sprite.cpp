#include "Sprite.h"
#include "Types.h"
#include "Texture.h"
#include "Object.h"
#include "Core/Window.h"
#include "Layers/SpriteRenderer.h"
#include "Core/LayerManager.h"

#include <stddef.h>

namespace S2DE {

	Sprite::~Sprite() {
		dynamic_cast<SpriteRenderer*>(LayerManager::GetLayer(m_layer))->DettachSprite(std::shared_ptr<Sprite>(this));
	}

	void Sprite::Init() {
		SetLayer(0);
	}

	void Sprite::Start() {
		
	}

	void Sprite::LateUpdate(float delta) {
		/*
		if (m_texture != NULL) {
			vec2f position = GetObject()->GetPosition();
			if (Centered) {
				position.x -= m_texture->GetWidth() / 2;
				position.y -= m_texture->GetHeight() / 2;
			}

			Window::ApplyTexture(*m_texture, (int)position.x, (int)position.y);
		}
		*/
	}

	void Sprite::SetTexture(std::shared_ptr<Texture> texture) {
		m_texture = texture;
	}


	std::shared_ptr<Texture> Sprite::GetTexture() {
		return m_texture;
	}


	void Sprite::SetLayer(int layer) {
		if(layer < 0) layer = 0;
		m_layer = layer;
		
		Layer* l = LayerManager::GetLayer(layer);
		if(l == nullptr) {
			l = LayerManager::CreateLayer<SpriteRenderer>(layer);
		}

		SpriteRenderer* sr = dynamic_cast<SpriteRenderer*>(l);
		if(sr == nullptr) return;

		sr->AttachSprite(std::shared_ptr<Sprite>(this));
	}

	int Sprite::GetLayer() { return m_layer; }

}