#ifndef S2DE_SPRITE_H
#define S2DE_SPRITE_H

#include "Component.h"
#include "Texture.h"

namespace S2DE {

    class Sprite : public Component {

	public:
		//Sprite() {}

        bool Centered;
		void Init();
		void Start();
		void LateUpdate(float delta);
        void SetTexture(Texture* texture);
		Texture* GetTexture();
		void SetLayer(int layer);
		int GetLayer();

	private:
		Texture* m_texture;
		int m_layer;

	};
}

#endif