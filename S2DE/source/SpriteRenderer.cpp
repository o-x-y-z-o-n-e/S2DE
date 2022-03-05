#include "Global.h"
#include "SpriteRenderer.h"
#include "Util.h"
#include "Types.h"
#include "Window.h"

namespace S2DE {


	int SpriteRenderer::FindEmptyIndex(Sprite* sprite) {
		int start = GetPointerHash(sprite) % SPRITE_TABLE_SIZE;
		int index = start;

		int i = 0;
		while (m_table[index] != nullptr)
			index = start + (i * i);

		return index;
	}


	int SpriteRenderer::FindSpriteIndex(Sprite* sprite) {
		int start = GetPointerHash(sprite) % SPRITE_TABLE_SIZE;
		int index = start;

		int i = 0;
		while (m_table[index] != nullptr) {
			if (m_table[index]->sprite == sprite)
				return index;

			index = start + (i * i);
		}

		return -1;
	}


	SpriteRenderer::~SpriteRenderer() {
		while (m_head != nullptr)
			DettachSprite(m_head->sprite);
	}


	void SpriteRenderer::Update() {
		SpriteNode* current = m_head;
		while (current != nullptr) {
			DrawSprite(*(current->sprite));

			current = current->next;
		}
	}


	void SpriteRenderer::AttachSprite(Sprite* sprite) {
		if (m_spriteCount >= SPRITE_TABLE_SIZE) {
			LogCoreError("Could not add new sprite (%s) to layer (%d)!", sprite->GetObject()->Name.c_str(), 0);
			return;
		}

		int index = FindEmptyIndex(sprite);

		SpriteNode* node = new SpriteNode();
		node->sprite = sprite;

		if (m_spriteCount == 0) {
			m_head = node;
			m_tail = node;
		} else {
			m_tail->next = node;
			node->prev = m_tail;
			m_tail = node;
		}

		m_table[index] = node;
		m_spriteCount++;
	}


	void SpriteRenderer::DrawSprite(Sprite& sprite) {
		Texture* tex = sprite.GetTexture();

		if (tex != nullptr) {
			vec2f position = sprite.GetObject()->GetPosition();
			if (sprite.Centered) {
				position.x -= tex->GetWidth() / 2;
				position.y -= tex->GetHeight() / 2;
			}
			Window::ApplyTexture(*tex, (int)position.x, (int)position.y);
		}
	}


	void SpriteRenderer::DettachSprite(Sprite* sprite) {
		int index = FindSpriteIndex(sprite);
		if (index < 0) return;

		SpriteNode* node = m_table[index];

		if (node->prev != nullptr)
			node->prev->next = node->next;
		
		if (node->next != nullptr)
			node->next->prev = node->prev;

		if (m_head == node)
			m_head = node->next;

		if (m_tail == node)
			m_tail = node->prev;

		m_table[index] = nullptr;
		m_spriteCount--;

		delete(node);
	}

}