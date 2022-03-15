#ifndef S2DE_SPRITE_RENDERER_H
#define S2DE_SPRITE_RENDERER_H

#include "Layer.h"
#include "Sprite.h"
#include "Types.h"

#include <list>
#include <memory>

namespace S2DE {


	class SpriteRenderer : public Layer {


	public:
		SpriteRenderer(int level);
		~SpriteRenderer();

		void Update(); //Render
		void AttachSprite(std::shared_ptr<Sprite> sprite);
		void DettachSprite(std::shared_ptr<Sprite> sprite);

	private:
		void DrawSprite(Sprite& sprite);
		std::list<std::shared_ptr<Sprite>> m_list;
		Dictionary m_table;
	};

}

#endif