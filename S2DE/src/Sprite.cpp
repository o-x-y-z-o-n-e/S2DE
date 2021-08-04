#include "Core.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "Object.h"

using namespace S2DE;

void Sprite::Init() {

}

void Sprite::Start() {

}

void Sprite::LateUpdate(float delta) {
	if(texture != NULL) {
		vect position = GetObject()->GetPosition();
		if(Centered) {
			position.x -= texture->GetWidth()/2;
			position.y -= texture->GetHeight()/2;
		}

		Window::ApplyTexture(texture, (int)position.x, (int)position.y);
	}
}

void Sprite::Dispose() {
	if (texture != NULL) {
		texture->Free();
		texture = NULL;
	}
}

void Sprite::SetTexture(Texture* texture) {
	this->texture = texture;
}
