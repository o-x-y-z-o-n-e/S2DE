#include "S2DE.h"
#include "Circle.h"

int main(int argc, char** args) {
	if(!S2DE::Init()) return 1;
	
	S2DE::SetTitle("Test App");

	S2DE::Object* testObj = S2DE::Object::Create("Test");
	S2DE::Texture* texture = S2DE::Texture::Load("resources/smile.bmp");
	S2DE::Sprite* testSprite = new S2DE::Sprite();
	testObj->AddComponent(testSprite);
	testSprite->SetTexture(texture);
	testSprite->Centered = true;

	Circle* testCircle = new Circle();
	testObj->AddComponent(testCircle);

	testObj->SetPosition(S2DE::vec2f(0, 0));

	S2DE::Camera::SetPosition(0, 0);

	S2DE::Log("Hello There!");

	S2DE::Start();

	return 0;
}