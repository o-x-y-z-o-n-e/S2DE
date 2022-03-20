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
		switch (scancode) {
		case SDL_SCANCODE_A:             return S2DE_KEY_A;
		case SDL_SCANCODE_B:             return S2DE_KEY_B;
		case SDL_SCANCODE_C:             return S2DE_KEY_C;
		case SDL_SCANCODE_D:             return S2DE_KEY_D;
		case SDL_SCANCODE_E:             return S2DE_KEY_E;
		case SDL_SCANCODE_F:             return S2DE_KEY_F;
		case SDL_SCANCODE_G:             return S2DE_KEY_G;
		case SDL_SCANCODE_H:             return S2DE_KEY_H;
		case SDL_SCANCODE_I:             return S2DE_KEY_I;
		case SDL_SCANCODE_J:             return S2DE_KEY_J;
		case SDL_SCANCODE_K:             return S2DE_KEY_K;
		case SDL_SCANCODE_L:             return S2DE_KEY_L;
		case SDL_SCANCODE_M:             return S2DE_KEY_M;
		case SDL_SCANCODE_N:             return S2DE_KEY_N;
		case SDL_SCANCODE_O:             return S2DE_KEY_O;
		case SDL_SCANCODE_P:             return S2DE_KEY_P;
		case SDL_SCANCODE_Q:             return S2DE_KEY_Q;
		case SDL_SCANCODE_R:             return S2DE_KEY_R;
		case SDL_SCANCODE_S:             return S2DE_KEY_S;
		case SDL_SCANCODE_T:             return S2DE_KEY_T;
		case SDL_SCANCODE_U:             return S2DE_KEY_U;
		case SDL_SCANCODE_V:             return S2DE_KEY_V;
		case SDL_SCANCODE_W:             return S2DE_KEY_W;
		case SDL_SCANCODE_X:             return S2DE_KEY_X;
		case SDL_SCANCODE_Y:             return S2DE_KEY_Y;
		case SDL_SCANCODE_Z:             return S2DE_KEY_Z;
		case SDL_SCANCODE_1:             return S2DE_KEY_1;
		case SDL_SCANCODE_2:             return S2DE_KEY_2;
		case SDL_SCANCODE_3:             return S2DE_KEY_3;
		case SDL_SCANCODE_4:             return S2DE_KEY_4;
		case SDL_SCANCODE_5:             return S2DE_KEY_5;
		case SDL_SCANCODE_6:             return S2DE_KEY_6;
		case SDL_SCANCODE_7:             return S2DE_KEY_7;
		case SDL_SCANCODE_8:             return S2DE_KEY_8;
		case SDL_SCANCODE_9:             return S2DE_KEY_9;
		case SDL_SCANCODE_0:             return S2DE_KEY_0;
		case SDL_SCANCODE_F1:            return S2DE_KEY_F1;			  
		case SDL_SCANCODE_F2:            return S2DE_KEY_F2;			  
		case SDL_SCANCODE_F3:            return S2DE_KEY_F3;			  
		case SDL_SCANCODE_F4:            return S2DE_KEY_F4;			  
		case SDL_SCANCODE_F5:            return S2DE_KEY_F5;			  
		case SDL_SCANCODE_F6:            return S2DE_KEY_F6;			  
		case SDL_SCANCODE_F7:            return S2DE_KEY_F7;			  
		case SDL_SCANCODE_F8:            return S2DE_KEY_F8;			  
		case SDL_SCANCODE_F9:            return S2DE_KEY_F9;			  
		case SDL_SCANCODE_F10:           return S2DE_KEY_F10;		  
		case SDL_SCANCODE_F11:           return S2DE_KEY_F11;		  
		case SDL_SCANCODE_F12:           return S2DE_KEY_F12;		  
		case SDL_SCANCODE_ESCAPE:        return S2DE_KEY_ESCAPE;		  
		case SDL_SCANCODE_GRAVE:         return S2DE_KEY_TILDE;		  
		case SDL_SCANCODE_TAB:           return S2DE_KEY_TAB;		  
		case SDL_SCANCODE_CAPSLOCK:      return S2DE_KEY_CAPS;		  
		case SDL_SCANCODE_LSHIFT:        return S2DE_KEY_L_SHIFT;	  
		case SDL_SCANCODE_LCTRL:         return S2DE_KEY_L_CTRL;		  
		case SDL_SCANCODE_LALT:          return S2DE_KEY_L_ALT;		  
		case SDL_SCANCODE_LGUI:	         return S2DE_KEY_L_MOD;		  
		case SDL_SCANCODE_RSHIFT:        return S2DE_KEY_R_SHIFT;	  
		case SDL_SCANCODE_RCTRL:         return S2DE_KEY_R_CTRL;		  
		case SDL_SCANCODE_RALT:          return S2DE_KEY_R_ALT;		  
		case SDL_SCANCODE_RGUI:          return S2DE_KEY_R_MOD;		  
		case SDL_SCANCODE_MINUS:         return S2DE_KEY_HYPHEN;		  
		case SDL_SCANCODE_EQUALS:        return S2DE_KEY_EQUAL;		  
		case SDL_SCANCODE_LEFTBRACKET:   return S2DE_KEY_L_BRACKET;	  
		case SDL_SCANCODE_RIGHTBRACKET:  return S2DE_KEY_R_BRACKET;	  
		case SDL_SCANCODE_SEMICOLON:     return S2DE_KEY_SEMICOLON;	  
		case SDL_SCANCODE_APOSTROPHE:    return S2DE_KEY_QUOTE;		  
		case SDL_SCANCODE_BACKSLASH:     return S2DE_KEY_BACKSLASH;	  
		case SDL_SCANCODE_COMMA:         return S2DE_KEY_COMMA;		  
		case SDL_SCANCODE_PERIOD:        return S2DE_KEY_PERIOD;		  
		case SDL_SCANCODE_SLASH:         return S2DE_KEY_SLASH;		  
		case SDL_SCANCODE_BACKSPACE:     return S2DE_KEY_BACKSPACE;	  
		case SDL_SCANCODE_RETURN:        return S2DE_KEY_RETURN;		  
		case SDL_SCANCODE_SPACE:         return S2DE_KEY_SPACE;		  
		case SDL_SCANCODE_UP:            return S2DE_KEY_UP;			  
		case SDL_SCANCODE_DOWN:          return S2DE_KEY_DOWN;		  
		case SDL_SCANCODE_LEFT:          return S2DE_KEY_LEFT;		  
		case SDL_SCANCODE_RIGHT:         return S2DE_KEY_RIGHT;		  
		case SDL_SCANCODE_INSERT:        return S2DE_KEY_INSERT;		  
		case SDL_SCANCODE_HOME:	         return S2DE_KEY_HOME;		  
		case SDL_SCANCODE_PAGEUP:        return S2DE_KEY_PAGE_UP;	  
		case SDL_SCANCODE_PAGEDOWN:      return S2DE_KEY_PAGE_DOWN;	  
		case SDL_SCANCODE_END:           return S2DE_KEY_END;		  
		case SDL_SCANCODE_DELETE:        return S2DE_KEY_DELETE;		  
		case SDL_SCANCODE_PRINTSCREEN:   return S2DE_KEY_PRINT_SCREEN; 
		case SDL_SCANCODE_SCROLLLOCK:    return S2DE_KEY_SCROLL_LOCK;  
		case SDL_SCANCODE_PAUSE:         return S2DE_KEY_PAUSE;		  
		case SDL_SCANCODE_MENU:          return S2DE_KEY_MENU;      

		default:                         return -1;
		}
	}

}