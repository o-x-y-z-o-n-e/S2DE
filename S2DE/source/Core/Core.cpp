#include "Global.h"
#include "Core.h"
#include "Application.h"
#include "Window.h"
#include "Console.h"
#include "Layer.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "LayerManager.h"
#include "Input.h"
#include "InputManager.h"

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
		InputManager::Flush();
		
		//SDL events
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_WINDOWEVENT: {
					Window::HandleWindowEvent(e.window);
					break;
				}

				case SDL_KEYDOWN: {
					int key = SDLToInput(e.key.keysym.scancode);
					InputManager::SetPress(key);

					break;
				}

				case SDL_KEYUP: {
					int key = SDLToInput(e.key.keysym.scancode);
					InputManager::SetRelease(key);
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
			//PhysicsManager::Step(s_fixedDeltaCounter);
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

		Window::SetRefreshRate(fps);
	}


	int Core::SDLToInput(int scancode) {
		int key = -1;
		switch (scancode) {
		case SDL_SCANCODE_A:             key = S2DE_KEY_A; break;
		case SDL_SCANCODE_B:             key = S2DE_KEY_B; break;
		case SDL_SCANCODE_C:             key = S2DE_KEY_C; break;
		case SDL_SCANCODE_D:             key = S2DE_KEY_D; break;
		case SDL_SCANCODE_E:             key = S2DE_KEY_E; break;
		case SDL_SCANCODE_F:             key = S2DE_KEY_F; break;
		case SDL_SCANCODE_G:             key = S2DE_KEY_G; break;
		case SDL_SCANCODE_H:             key = S2DE_KEY_H; break;
		case SDL_SCANCODE_I:             key = S2DE_KEY_I; break;
		case SDL_SCANCODE_J:             key = S2DE_KEY_J; break;
		case SDL_SCANCODE_K:             key = S2DE_KEY_K; break;
		case SDL_SCANCODE_L:             key = S2DE_KEY_L; break;
		case SDL_SCANCODE_M:             key = S2DE_KEY_M; break;
		case SDL_SCANCODE_N:             key = S2DE_KEY_N; break;
		case SDL_SCANCODE_O:             key = S2DE_KEY_O; break;
		case SDL_SCANCODE_P:             key = S2DE_KEY_P; break;
		case SDL_SCANCODE_Q:             key = S2DE_KEY_Q; break;
		case SDL_SCANCODE_R:             key = S2DE_KEY_R; break;
		case SDL_SCANCODE_S:             key = S2DE_KEY_S; break;
		case SDL_SCANCODE_T:             key = S2DE_KEY_T; break;
		case SDL_SCANCODE_U:             key = S2DE_KEY_U; break;
		case SDL_SCANCODE_V:             key = S2DE_KEY_V; break;
		case SDL_SCANCODE_W:             key = S2DE_KEY_W; break;
		case SDL_SCANCODE_X:             key = S2DE_KEY_X; break;
		case SDL_SCANCODE_Y:             key = S2DE_KEY_Y; break;
		case SDL_SCANCODE_Z:             key = S2DE_KEY_Z; break;
		case SDL_SCANCODE_1:             key = S2DE_KEY_1; break;
		case SDL_SCANCODE_2:             key = S2DE_KEY_2; break;
		case SDL_SCANCODE_3:             key = S2DE_KEY_3; break;
		case SDL_SCANCODE_4:             key = S2DE_KEY_4; break;
		case SDL_SCANCODE_5:             key = S2DE_KEY_5; break;
		case SDL_SCANCODE_6:             key = S2DE_KEY_6; break;
		case SDL_SCANCODE_7:             key = S2DE_KEY_7; break;
		case SDL_SCANCODE_8:             key = S2DE_KEY_8; break;
		case SDL_SCANCODE_9:             key = S2DE_KEY_9; break;
		case SDL_SCANCODE_0:             key = S2DE_KEY_0; break;
		case SDL_SCANCODE_F1:            key = S2DE_KEY_F1;			  break;
		case SDL_SCANCODE_F2:            key = S2DE_KEY_F2;			  break;
		case SDL_SCANCODE_F3:            key = S2DE_KEY_F3;			  break;
		case SDL_SCANCODE_F4:            key = S2DE_KEY_F4;			  break;
		case SDL_SCANCODE_F5:            key = S2DE_KEY_F5;			  break;
		case SDL_SCANCODE_F6:            key = S2DE_KEY_F6;			  break;
		case SDL_SCANCODE_F7:            key = S2DE_KEY_F7;			  break;
		case SDL_SCANCODE_F8:            key = S2DE_KEY_F8;			  break;
		case SDL_SCANCODE_F9:            key = S2DE_KEY_F9;			  break;
		case SDL_SCANCODE_F10:           key = S2DE_KEY_F10;		  break;
		case SDL_SCANCODE_F11:           key = S2DE_KEY_F11;		  break;
		case SDL_SCANCODE_F12:           key = S2DE_KEY_F12;		  break;
		case SDL_SCANCODE_ESCAPE:        key = S2DE_KEY_ESCAPE;		  break;
		case SDL_SCANCODE_GRAVE:         key = S2DE_KEY_TILDE;		  break;
		case SDL_SCANCODE_TAB:           key = S2DE_KEY_TAB;		  break;
		case SDL_SCANCODE_CAPSLOCK:      key = S2DE_KEY_CAPS;		  break;
		case SDL_SCANCODE_LSHIFT:        key = S2DE_KEY_L_SHIFT;	  break;
		case SDL_SCANCODE_LCTRL:         key = S2DE_KEY_L_CTRL;		  break;
		case SDL_SCANCODE_LALT:          key = S2DE_KEY_L_ALT;		  break;
		case SDL_SCANCODE_LGUI:	         key = S2DE_KEY_L_MOD;		  break;
		case SDL_SCANCODE_RSHIFT:        key = S2DE_KEY_R_SHIFT;	  break;
		case SDL_SCANCODE_RCTRL:         key = S2DE_KEY_R_CTRL;		  break;
		case SDL_SCANCODE_RALT:          key = S2DE_KEY_R_ALT;		  break;
		case SDL_SCANCODE_RGUI:          key = S2DE_KEY_R_MOD;		  break;
		case SDL_SCANCODE_MINUS:         key = S2DE_KEY_HYPHEN;		  break;
		case SDL_SCANCODE_EQUALS:        key = S2DE_KEY_EQUAL;		  break;
		case SDL_SCANCODE_LEFTBRACKET:   key = S2DE_KEY_L_BRACKET;	  break;
		case SDL_SCANCODE_RIGHTBRACKET:  key = S2DE_KEY_R_BRACKET;	  break;
		case SDL_SCANCODE_SEMICOLON:     key = S2DE_KEY_SEMICOLON;	  break;
		case SDL_SCANCODE_APOSTROPHE:    key = S2DE_KEY_QUOTE;		  break;
		case SDL_SCANCODE_BACKSLASH:     key = S2DE_KEY_BACKSLASH;	  break;
		case SDL_SCANCODE_COMMA:         key = S2DE_KEY_COMMA;		  break;
		case SDL_SCANCODE_PERIOD:        key = S2DE_KEY_PERIOD;		  break;
		case SDL_SCANCODE_SLASH:         key = S2DE_KEY_SLASH;		  break;
		case SDL_SCANCODE_BACKSPACE:     key = S2DE_KEY_BACKSPACE;	  break;
		case SDL_SCANCODE_RETURN:        key = S2DE_KEY_RETURN;		  break;
		case SDL_SCANCODE_SPACE:         key = S2DE_KEY_SPACE;		  break;
		case SDL_SCANCODE_UP:            key = S2DE_KEY_UP;			  break;
		case SDL_SCANCODE_DOWN:          key = S2DE_KEY_DOWN;		  break;
		case SDL_SCANCODE_LEFT:          key = S2DE_KEY_LEFT;		  break;
		case SDL_SCANCODE_RIGHT:         key = S2DE_KEY_RIGHT;		  break;
		case SDL_SCANCODE_INSERT:        key = S2DE_KEY_INSERT;		  break;
		case SDL_SCANCODE_HOME:	         key = S2DE_KEY_HOME;		  break;
		case SDL_SCANCODE_PAGEUP:        key = S2DE_KEY_PAGE_UP;	  break;
		case SDL_SCANCODE_PAGEDOWN:      key = S2DE_KEY_PAGE_DOWN;	  break;
		case SDL_SCANCODE_END:           key = S2DE_KEY_END;		  break;
		case SDL_SCANCODE_DELETE:        key = S2DE_KEY_DELETE;		  break;
		case SDL_SCANCODE_PRINTSCREEN:   key = S2DE_KEY_PRINT_SCREEN; break;
		case SDL_SCANCODE_SCROLLLOCK:    key = S2DE_KEY_SCROLL_LOCK;  break;
		case SDL_SCANCODE_PAUSE:         key = S2DE_KEY_PAUSE;		  break;
		case SDL_SCANCODE_MENU:          key = S2DE_KEY_MENU;         break;
		default: key = -1; break;
		}

		return key;
	}

}