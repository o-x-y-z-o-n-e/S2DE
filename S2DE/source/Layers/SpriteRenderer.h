#ifndef S2DE_SPRITE_RENDERER_H
#define S2DE_SPRITE_RENDERER_H

#include "Layer.h"
#include "Sprite.h"
#include "Types.h"

namespace S2DE {


	class SpriteRenderer : public Layer {


	public:
		SpriteRenderer(int level);
		~SpriteRenderer();

		void Update(); //Render
		void AttachSprite(Sprite* sprite);
		void DettachSprite(Sprite* sprite);

	private:
		void DrawSprite(Sprite& sprite);
		Chain<Sprite*> m_list;
		Dictionary m_table;
	};

}

#endif