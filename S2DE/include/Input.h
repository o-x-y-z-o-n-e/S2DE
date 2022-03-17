#ifndef S2DE_INPUT_H
#define S2DE_INPUT_H

//283 total keys

#define S2DE_KEY_A 97
#define S2DE_KEY_D 100
#define S2DE_KEY_SPACE 32


namespace S2DE {

	class Input {

	public:
		static bool IsPressed(int key);
		static bool IsHeld(int key);
		static bool IsReleased(int key);

	};

}

#endif