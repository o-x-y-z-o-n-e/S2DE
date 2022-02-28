#include "S2DE.h"
#include "Window.h"
#include "ObjectManager.h"
#include "TextureManager.h"

#include <iostream>

#define FIXED_TIME_STEP 0.01666666f

namespace S2DE {

	bool hasInit;
	bool isRunning;
	SDL_Event e;
	int tickCounter;
	float fixedDeltaCounter;


	bool IsRunning() { return isRunning; };


	int Init() {
		if (hasInit) {
			printf("[S2DE] Already Initialized!\n");
			return 0;
		}

		printf("[S2DE] Initializing...\n");

		//Init components here
		if (!Window::Init()) return 0;
		InitTextureManager();

		hasInit = true;
		return 1;
	}


	void Start() {
		if (!hasInit) return;

		printf("[S2DE] Starting...\n");

		isRunning = true;

		StartAllObjects();

		while (isRunning)
			Loop();
	}

	void Close() {
		if (!isRunning) return;

		printf("[S2DE] Closing...\n");

		isRunning = false;

		Window::Close();
	}


	void Loop() {
		DestroyMarkedObjects();

		//Input::Flush();
		// 
		//SDL events
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				Close();
				return;
			} else if (e.type == SDL_KEYDOWN) {
				//		Input::SetPress(e.key.keysym.sym);
			}
		}
		
		int currentTick = SDL_GetTicks();
		int tickDelta = currentTick - tickCounter;
		float timeDelta = tickDelta / 1000.0f;
		tickCounter = currentTick;
		fixedDeltaCounter += timeDelta;

		if (fixedDeltaCounter > FIXED_TIME_STEP) {
			FixedUpdateAllObjects(fixedDeltaCounter);

			fixedDeltaCounter -= FIXED_TIME_STEP;
		}

		//clears all graphics
		Window::Clear();

		//update gameplay
		DynamicUpdateAllObjects(timeDelta);
		LateUpdateAllObjects(timeDelta);

		//update graphics
		Window::Update();

		//input press switch
		//Input::CheckRelease();
	}

}