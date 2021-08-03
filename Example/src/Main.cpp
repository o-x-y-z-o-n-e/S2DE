#define SDL_MAIN_HANDLED
#include <S2DE.h>
#include "Player.h"

using namespace S2DE;

Object* gridObj;
Sprite* grid;

Object* playerObj;
Player* player;
Sprite* playerSprite;

int main(int argc, char** args) {

	if(Core::Init() < 0) return -1;

	Input::AddBinding("up", SDLK_UP);
	Input::AddBinding("down", SDLK_DOWN);
	Input::AddBinding("left", SDLK_LEFT);
	Input::AddBinding("right", SDLK_RIGHT);

	gridObj = Object::Create("Grid");
	grid = new Sprite();
	gridObj->AddComponent(grid);
	Texture* gridTex = new Texture();
	gridTex->Load("/home/jeremy/Desktop/S2DE/bin/res/grid.png");
	grid->SetTexture(gridTex);
	gridObj->SetPosition(*new Vector(0, 0));
	grid->Centered = true;

	playerObj = Object::Create("Player");
	player = new Player();
	playerObj->AddComponent(player);
	playerSprite = new Sprite();
	playerObj->AddComponent(playerSprite);
	Texture* playerTex = new Texture();
	playerTex->Load("/home/jeremy/Desktop/S2DE/bin/res/smile.png");
	playerSprite->SetTexture(playerTex);
	playerObj->SetPosition(*new Vector(0, 0));
	playerSprite->Centered = true;

	Core::Start();

	return 0;
}
