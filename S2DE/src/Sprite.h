#pragma once

#include "Component.h"

namespace S2DE {

    //class Component;
    class Texture;

    class Sprite : public Component {

	public:
        bool Centered;
		void Init();
		void Start();
		void Update(float delta);
		void Dispose();
        void SetTexture(Texture* texture);

	private:
		Texture* texture;

	};
}
