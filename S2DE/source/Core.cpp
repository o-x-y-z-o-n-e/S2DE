#include "Application.h"
#include "Global.h"
#include "Core.h"
#include "Window.h"
#include "Console.h"
#include "ObjectManager.h"
#include "TextureManager.h"

#include <iostream>

#define FIXED_TIME_STEP 0.01666666F

namespace S2DE {

	int Init() { return Core::Init(); }
	void Start() { Core::Start(); }
	void Close() { Core::Close(); }
	bool IsRunning() { return Core::IsRunning(); }
	void SetTargetFrameRate(int fps) { Core::SetTargetFrameRate(fps); }


	bool Core::m_hasInit;
	bool Core::m_isRunning;
	int Core::m_tickCounter;

	float Core::m_fixedDeltaCounter;

	float Core::m_renderTimeStep;
	float Core::m_renderTickCounter;

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

			switch (e.type) {
				case SDL_WINDOWEVENT: {
					Window::HandleWindowEvent(&e.window);
					break;
				}

				case SDL_QUIT: {
					Close();
					break;
				}
			}
		}
		
		int currentTick = SDL_GetTicks();
		int tickDelta = currentTick - m_tickCounter;
		float timeDelta = tickDelta * 0.001F;    //same as 'tickDelta / 1000.0F'
		m_tickCounter = currentTick;

		m_fixedDeltaCounter += timeDelta;
		m_renderTickCounter += timeDelta;

		bool render = false;
		if (m_renderTickCounter > m_renderTimeStep) {
			m_renderTickCounter = 0;
			render = true;
		}

		if (m_fixedDeltaCounter > FIXED_TIME_STEP) {
			ObjectManager::FixedUpdateAllObjects(m_fixedDeltaCounter);
			m_fixedDeltaCounter -= FIXED_TIME_STEP;
		}

		//clears all graphics
		if(render)
			Window::Clear();

		//update gameplay
		ObjectManager::DynamicUpdateAllObjects(timeDelta);
		ObjectManager::LateUpdateAllObjects(timeDelta);

		//update graphics
		if(render)
			Window::Update();

		//input press switch
		//Input::CheckRelease();
	}


	void Core::SetTargetFrameRate(int fps) {
		if (fps < 1)
			m_renderTimeStep = 0.0F;
		else
			m_renderTimeStep = 1.0F / (float)fps;
	}

}