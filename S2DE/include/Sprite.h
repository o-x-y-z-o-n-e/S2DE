#ifndef S2DE_SPRITE_H
#define S2DE_SPRITE_H

#include "Component.h"
#include "Texture.h"

#include <memory>

namespace S2DE {

    class Sprite : public Component {

	public:
		//Sprite() {}

        bool Centered;
		void Init();
		void Start();
		void LateUpdate(float delta);
        void SetTexture(std::shared_ptr<Texture> texture);
		std::shared_ptr<Texture> GetTexture();
		void SetLayer(int layer);
		int GetLayer();

	private:
		std::shared_ptr<Texture> m_texture;
		int m_layer;

	};
}

#endif