#include "S2DE.h"
#include "Circle.h"

#include <memory>

int main(int argc, char** args) {
	if(!S2DE::Init()) return 1;
	
	S2DE::SetTitle("Test App");

	S2DE::Object* testObj = S2DE::Object::Create("Test");
	std::shared_ptr<S2DE::Texture> texture = S2DE::Texture::Load("resources/smile.bmp");
	std::shared_ptr<S2DE::Sprite> testSprite = std::make_shared<S2DE::Sprite>();
	testObj->AddComponent(testSprite);
	testSprite->SetTexture(texture);
	testSprite->Centered = true;

	std::shared_ptr<Circle> testCircle = std::make_shared<Circle>();
	testObj->AddComponent(testCircle);

	testObj->SetLocalPosition(S2DE::vec2f(0, 0));

	S2DE::Camera::SetPosition(0, 0);

	S2DE::Log("Hello There!");

	S2DE::Start();

	return 0;
}