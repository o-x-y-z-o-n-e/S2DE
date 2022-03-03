#include "Application.h"
#include "Core.h"
#include "Window.h"
#include "Console.h"
#include "ObjectManager.h"
#include "TextureManager.h"

#include <iostream>

#define FIXED_TIME_STEP 0.01666666f

namespace S2DE {

	int Init() { return Core::Init(); }
	void Start() { Core::Start(); }
	void Close() { Core::Close(); }
	bool IsRunning() { return Core::IsRunning(); }



	bool Core::m_hasInit;
	bool Core::m_isRunning;
	int Core::m_tickCounter;
	float Core::m_fixedDeltaCounter;

	bool Core::IsRunning() { return m_isRunning; };

	int Core::Init() {
		Console::Init();

		if (m_hasInit) {
			LogCoreWarning("Already Initialized!");
			return 0;
		}

		LogCore("Initializing...");

		//Init components here
		if (!Window::Init()) return 0;
		TextureManager::Init();

		m_hasInit = true;
		return 1;
	}


	void Core::Start() {
		if (!m_hasInit) return;

		LogCore("Starting...");

		m_isRunning = true;

		ObjectManager::StartAllObjects();

		while (m_isRunning)
			Loop();
	}


	void Core::Close() {
		if (!m_isRunning) return;

		LogCore("Closing...");

		m_isRunning = false;

		Window::Close();
	}


	void Core::Loop() {
		ObjectManager::DestroyMarkedObjects();

		//Input::Flush();
		// 
		//SDL events
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				Close();
				return;
			} else if (e.type == SDL_KEYDOWN) {
				//		Input::SetPress(e.key.keysym.sym);
			}
		}
		
		int currentTick = SDL_GetTicks();
		int tickDelta = currentTick - m_tickCounter;
		float timeDelta = tickDelta / 1000.0F;
		m_tickCounter = currentTick;
		m_fixedDeltaCounter += timeDelta;

		if (m_fixedDeltaCounter > FIXED_TIME_STEP) {
			ObjectManager::FixedUpdateAllObjects(m_fixedDeltaCounter);

			m_fixedDeltaCounter -= FIXED_TIME_STEP;
		}

		//clears all graphics
		Window::Clear();

		//update gameplay
		ObjectManager::DynamicUpdateAllObjects(timeDelta);
		ObjectManager::LateUpdateAllObjects(timeDelta);

		//update graphics
		Window::Update();

		//input press switch
		//Input::CheckRelease();
	}

}