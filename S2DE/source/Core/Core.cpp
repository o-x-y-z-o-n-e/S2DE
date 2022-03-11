#include "Global.h"
#include "Core.h"
#include "Application.h"
#include "Window.h"
#include "Console.h"
#include "Layer.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "LayerManager.h"

#include <iostream>

#define FIXED_TIME_STEP 0.01666666F

namespace S2DE {

	int Init() { return Core::Init(); }
	void Start() { Core::Start(); }
	void Close() { Core::Close(); }
	bool IsRunning() { return Core::IsRunning(); }
	void SetTargetFrameRate(int fps) { Core::SetTargetFrameRate(fps); }


	bool Core::s_hasInit;
	bool Core::s_isRunning;
	int Core::s_tickCounter;

	float Core::s_fixedDeltaCounter;

	float Core::s_renderTimeStep;
	float Core::s_renderTickCounter;

	bool Core::IsRunning() { return s_isRunning; };

	int Core::Init() {
		if (s_hasInit) {
			LogCoreWarning("Already Initialized!");
			return 0;
		}

		Console::Init();

		LogCore("Initializing...");

		//Init components here
		if (!Window::Init()) return 0;
		TextureManager::Init();
		ObjectManager::Init();

		s_hasInit = true;
		return 1;
	}


	void Core::Start() {
		if (!s_hasInit) return;

		LogCore("Starting...");

		s_isRunning = true;

		ObjectManager::StartAllObjects();

		while (s_isRunning)
			Loop();
	}


	void Core::Close() {
		if (!s_hasInit) return;
		if (!s_isRunning) return;

		LogCore("Closing...");

		s_isRunning = false;

		Window::Close();
	}


	void Core::Loop() {
		ObjectManager::DestroyMarkedObjects();

		//Input::Flush();
		// 
		//SDL events
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {

			switch (e.type) {
				case SDL_WINDOWEVENT: {
					Window::HandleWindowEvent(e.window);
					break;
				}

				case SDL_QUIT: {
					Close();
					break;
				}
			}
		}
		
		int currentTick = SDL_GetTicks();
		int tickDelta = currentTick - s_tickCounter;
		float timeDelta = tickDelta * 0.001F;    //same as 'tickDelta / 1000.0F'
		s_tickCounter = currentTick;

		s_fixedDeltaCounter += timeDelta;
		s_renderTickCounter += timeDelta;

		bool render = false;
		if (s_renderTickCounter > s_renderTimeStep) {
			s_renderTickCounter = 0;
			render = true;
		}

		if (s_fixedDeltaCounter > FIXED_TIME_STEP) {
			ObjectManager::FixedUpdateAllObjects(s_fixedDeltaCounter);
			s_fixedDeltaCounter -= FIXED_TIME_STEP;
		}

		//update gameplay
		ObjectManager::DynamicUpdateAllObjects(timeDelta);
		ObjectManager::LateUpdateAllObjects(timeDelta);

		//update graphics
		if(render) {
			Window::Clear();
			LayerManager::Process();
			Window::Update();
		}

		//input press switch
		//Input::CheckRelease();
	}


	void Core::SetTargetFrameRate(int fps) {
		if (fps < 1)
			s_renderTimeStep = 0.0F;
		else
			s_renderTimeStep = 1.0F / (float)fps;
	}

}