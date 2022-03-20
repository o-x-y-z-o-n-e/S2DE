#include "Input.h"
#include "InputManager.h"

namespace S2DE {

	bool InputManager::s_pressStates[S2DE_KEYS];
	bool InputManager::s_heldStates[S2DE_KEYS];
	bool InputManager::s_releaseStates[S2DE_KEYS];



	void InputManager::SetPress(int key) {
		if (s_heldStates[key])
			return;

		s_pressStates[key] = true;
		s_heldStates[key] = true;
	}

	void InputManager::SetRelease(int key) {
		s_releaseStates[key] = true;
		s_heldStates[key] = false;
	}

	void InputManager::Flush() {
		for (int i = 0; i < S2DE_KEYS; i++) {
			s_pressStates[i] = false;
			s_releaseStates[i] = false;
		}
	}


	bool InputManager::GetPress(int key) {
		if (key < 0 || key >= S2DE_KEYS)
			return false;

		return s_pressStates[key];
	}


	bool InputManager::GetHeld(int key) {
		if (key < 0 || key >= S2DE_KEYS)
			return false;

		return s_heldStates[key];
	}


	bool InputManager::GetRelease(int key) {
		if (key < 0 || key >= S2DE_KEYS)
			return false;

		return s_releaseStates[key];
	}


	bool Input::IsPressed(int key) { return InputManager::GetPress(key); }
	bool Input::IsHeld(int key) { return InputManager::GetHeld(key); }
	bool Input::IsReleased(int key) { return InputManager::GetRelease(key); }
}