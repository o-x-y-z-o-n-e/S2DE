#include "Core.h"
#include "Input.h"
#include "Window.h"
#include "Object.h"

#include <iostream>
#include <SDL2/SDL.h>


using namespace S2DE;

const float FIXED_TIME_STEP = 0.01666666f;

static bool hasInit;
static bool isRunning;
static SDL_Event e;
static int tickCounter;
static float fixedDeltaCounter;

bool Core::IsRunning() { return isRunning; };

int Core::Init() {
	if (hasInit) return -1;

	printf("[S2DE] Init...\n");

	if (Window::Init() < 0) return -1;

	hasInit = true;

	return 0;
}


void Core::Start() {
	if (!hasInit) return;

	printf("[S2DE] Starting...\n");

	isRunning = true;

	Object::StartAll();

	while (isRunning) Loop();
}

void Core::Close() {
	if (!isRunning) return;

	printf("[S2DE] Closing...\n");

	isRunning = false;

	Window::Close();
	Object::DisposeAll();
}


void Core::Loop() {
	//SDL events
	Input::Flush();
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT) {
			Core::Close();
			return;
		} else if (e.type == SDL_KEYDOWN) {
			Input::SetPress(e.key.keysym.sym);
		}
	}

	int currentTick = SDL_GetTicks();
	int tickDelta = currentTick - tickCounter;
	float timeDelta = tickDelta / 1000.0f;
	tickCounter = currentTick;
	fixedDeltaCounter += timeDelta;

	if(fixedDeltaCounter >= FIXED_TIME_STEP) {
		Object::FixedUpdateAll(fixedDeltaCounter);

		//fixedDeltaCounter -= FIXED_TIME_STEP;
		fixedDeltaCounter = 0;
	}

	//clears all graphics
	Window::Clear();

	//update gameplay
	Object::DynamicUpdateAll(timeDelta);
	Object::LateUpdateAll(timeDelta);

	//update graphics
	Window::Update();

	//input press switch
	Input::CheckRelease();
}
