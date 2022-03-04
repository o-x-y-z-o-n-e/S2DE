#define SDL_MAIN_HANDLED

#include "S2DE.h"

int main(int argc, char** args) {
	if(!S2DE::Init()) return 1;

	S2DE::Object* testObj = S2DE::Object::Create("Test");
	S2DE::Texture* texture = S2DE::Texture::Load("resources/smile.bmp");
	S2DE::Sprite* testSprite = new S2DE::Sprite();
	testObj->AddComponent(testSprite);
	testSprite->SetTexture(texture);

	testObj->SetPosition(S2DE::vec2f(50, 50));

	S2DE::Log("Hello There!");

	S2DE::Start();

	return 0;
}