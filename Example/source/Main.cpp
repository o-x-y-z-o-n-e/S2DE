#define SDL_MAIN_HANDLED

#include "S2DE.h"

int main(int argc, char** args) {
	if(!S2DE::Init()) return 1;

	S2DE::Object* testObj = S2DE::Object::Create("Test");
	S2DE::Texture* texture = new S2DE::Texture();
	S2DE::Sprite* testSprite = new S2DE::Sprite();
	testObj->AddComponent(testSprite);
	testSprite->SetTexture(texture);

	texture->Load("resources/smile.bmp");

	testObj->SetPosition(S2DE::vec2f(50, 50));

	S2DE::Start();

	return 0;
}