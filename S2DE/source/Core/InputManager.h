#ifndef S2DE_INPUT_MANAGER
#define S2DE_INPUT_MANAGER

#define S2DE_KEYS 87

namespace S2DE {

	class InputManager {

	public:
		static void SetPress(int key);
		static void SetRelease(int key);
		static void Flush();

		static bool GetPress(int key);
		static bool GetHeld(int key);
		static bool GetRelease(int key);

	private:
		static bool s_pressStates[S2DE_KEYS];
		static bool s_heldStates[S2DE_KEYS];
		static bool s_releaseStates[S2DE_KEYS];
	};

}

#endif