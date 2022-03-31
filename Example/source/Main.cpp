#include "S2DE.h"
#include "Circle.h"
#include "Player.h"

#include <memory>

int main(int argc, char** args) {
	if(!S2DE::Init()) return 1;
	
	S2DE::SetTitle("Test App");
	S2DE::SetWindowMode(S2DE_WINDOWED);

	std::shared_ptr<S2DE::Texture> floorTexture = S2DE::Texture::Load("resources/floor.bmp");
	std::shared_ptr<S2DE::Object> floorObj = S2DE::Object::Create("Floor");
	std::shared_ptr<S2DE::Collider> floorCollider = floorObj->CreateComponent<S2DE::Collider>();
	std::shared_ptr<S2DE::Sprite> floorSprite = floorObj->CreateComponent<S2DE::Sprite>();

	floorCollider->SetSize({ 128, 16 });
	floorObj->SetWorldPosition({ -64, -16 });
	floorSprite->SetTexture(floorTexture);

	std::shared_ptr<S2DE::Object> testObj = S2DE::Object::Create("Test");
	std::shared_ptr<S2DE::Texture> testTexture = S2DE::Texture::Load("resources/smile.bmp");
	std::shared_ptr<S2DE::Sprite> testSprite = testObj->CreateComponent<S2DE::Sprite>();
	std::shared_ptr<Player> testPlayer = testObj->CreateComponent<Player>();

	testPlayer->SetSize({16, 16});
	testPlayer->SetOffset({-8, -8});
	testPlayer->SetLayer(1);
	testSprite->SetTexture(testTexture);
	testSprite->Centered = true;
	testObj->SetLocalPosition(S2DE::vec2f(0, 8));

	S2DE::Camera::SetPosition(0, 0);

	S2DE::Log("Hello There!");

	S2DE::Start();

	return 0;
}