#ifndef S2DE_SPRITE_RENDERER_H
#define S2DE_SPRITE_RENDERER_H

#include "Layer.h"
#include "Sprite.h"

#define SPRITE_TABLE_SIZE 10000

namespace S2DE {

	class SpriteNode;
	class SpriteNode {
	public:
		Sprite* sprite;
		SpriteNode* next;
		SpriteNode* prev;

	};


	class SpriteRenderer : Layer {

	public:
		~SpriteRenderer();

		void Update(); //Render
		void AttachSprite(Sprite* sprite);
		void DettachSprite(Sprite* sprite);

	private:
		int FindEmptyIndex(Sprite* sprite);
		int FindSpriteIndex(Sprite* sprite);
		void DrawSprite(Sprite& sprite);

		int m_spriteCount;
		SpriteNode* m_table[SPRITE_TABLE_SIZE];
		SpriteNode* m_head;
		SpriteNode* m_tail;

	};

}

#endif