#include "SpriteRenderer.h"
#include "Core/Global.h"
#include "Core/Util.h"
#include "Core/Window.h"
#include "Types.h"

// #define USE_HASH_TABLE
#define HASH_TABLE_SIZE 10000

namespace S2DE {


	SpriteRenderer::SpriteRenderer(int level) : Layer(level) {
#ifdef USE_HASH_TABLE
		m_table = Dictionary(HASH_TABLE_SIZE);
#endif
	}


	
	SpriteRenderer::~SpriteRenderer() {
		m_list.clear();
#ifdef USE_HASH_TABLE
		m_table.~Dictionary();
#endif
	}
	


	void SpriteRenderer::Update() {
		std::list<std::shared_ptr<Sprite>>::iterator it;
		for (it = m_list.begin(); it != m_list.end(); it++)
			DrawSprite(*(it->get()));
	}


	void SpriteRenderer::AttachSprite(std::shared_ptr<Sprite> sprite) {
#ifdef USE_HASH_TABLE
		if (m_table.Count() >= m_table.Max()) {
			LogCoreError("Could not add sprite (%s) to layer (%d)", sprite->GetObject()->Name, GetLevel());
			return;
		}
#endif

		m_list.push_back(sprite);

		// EDIT: We want to get the Chain::Node and input that into the hash table (with sprite* as the key).
#ifdef USE_HASH_TABLE
		m_table.Add(sprite, nullptr);
#endif
	}


	void SpriteRenderer::DrawSprite(Sprite& sprite) {
		std::shared_ptr<Texture> tex = sprite.GetTexture();

		if (tex.get() != nullptr) {
			vec2f position = sprite.GetObject()->GetWorldPosition();
			if (sprite.Centered) {
				position.x -= tex->GetWidth() / 2;
				position.y -= tex->GetHeight() / 2;
			}
			Window::ApplyTexture(*(tex.get()), (int)position.x, (int)position.y);
		}
	}


	void SpriteRenderer::DettachSprite(std::shared_ptr<Sprite> sprite) {
#ifdef USE_HASH_TABLE
		m_list.Remove(m_table.Get(sprite));
		m_table.Remove(sprite);
#else
		m_list.remove(sprite);
#endif
	}

}