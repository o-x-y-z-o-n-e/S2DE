#ifndef S2DE_SPRITE_H
#define S2DE_SPRITE_H

#include "Component.h"

namespace S2DE {

    class Texture;

    class Sprite : public Component {

	public:
		~Sprite();

        bool Centered;
		void Init();
		void Start();
		void LateUpdate(float delta);
        void SetTexture(Texture* texture);

	private:
		Texture* m_texture = nullptr;

	};
}

#endif