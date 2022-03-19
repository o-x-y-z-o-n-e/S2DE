#ifndef S2DE_INPUT_H
#define S2DE_INPUT_H

//283 total keys

#define S2DE_KEY_A 0
#define S2DE_KEY_B 1
#define S2DE_KEY_C 2
#define S2DE_KEY_D 3
#define S2DE_KEY_E 4
#define S2DE_KEY_F 5
#define S2DE_KEY_G 6
#define S2DE_KEY_H 7
#define S2DE_KEY_I 8
#define S2DE_KEY_J 9
#define S2DE_KEY_K 10
#define S2DE_KEY_L 11
#define S2DE_KEY_M 12
#define S2DE_KEY_N 13
#define S2DE_KEY_O 14
#define S2DE_KEY_P 15
#define S2DE_KEY_Q 16
#define S2DE_KEY_R 17
#define S2DE_KEY_S 18
#define S2DE_KEY_T 19
#define S2DE_KEY_U 20
#define S2DE_KEY_V 21
#define S2DE_KEY_W 22
#define S2DE_KEY_X 23
#define S2DE_KEY_Y 24
#define S2DE_KEY_Z 25
#define S2DE_KEY_1 26
#define S2DE_KEY_2 27
#define S2DE_KEY_3 28
#define S2DE_KEY_4 29
#define S2DE_KEY_5 30
#define S2DE_KEY_6 31
#define S2DE_KEY_7 32
#define S2DE_KEY_8 33
#define S2DE_KEY_9 34
#define S2DE_KEY_0 35
#define S2DE_KEY_F1 36
#define S2DE_KEY_F2 37
#define S2DE_KEY_F3 38
#define S2DE_KEY_F4 39
#define S2DE_KEY_F5 40
#define S2DE_KEY_F6 41
#define S2DE_KEY_F7 42
#define S2DE_KEY_F8 43
#define S2DE_KEY_F9 44
#define S2DE_KEY_F10 45
#define S2DE_KEY_F11 46
#define S2DE_KEY_F12 47
#define S2DE_KEY_ESCAPE 48
#define S2DE_KEY_TILDE 49
#define S2DE_KEY_TAB 50
#define S2DE_KEY_CAPS 51
#define S2DE_KEY_L_SHIFT 52
#define S2DE_KEY_L_CTRL 53
#define S2DE_KEY_L_ALT 54
#define S2DE_KEY_L_MOD 55
#define S2DE_KEY_R_SHIFT 56
#define S2DE_KEY_R_CTRL 57
#define S2DE_KEY_R_ALT 58
#define S2DE_KEY_R_MOD 59
#define S2DE_KEY_HYPHEN 60
#define S2DE_KEY_EQUAL 61
#define S2DE_KEY_L_BRACKET 62
#define S2DE_KEY_R_BRACKET 63
#define S2DE_KEY_SEMICOLON 64
#define S2DE_KEY_QUOTE 65
#define S2DE_KEY_BACKSLASH 66
#define S2DE_KEY_COMMA 67
#define S2DE_KEY_PERIOD 68
#define S2DE_KEY_SLASH 69
#define S2DE_KEY_BACKSPACE 70
#define S2DE_KEY_RETURN 71
#define S2DE_KEY_SPACE 72
#define S2DE_KEY_UP 73
#define S2DE_KEY_DOWN 74
#define S2DE_KEY_LEFT 75
#define S2DE_KEY_RIGHT 76
#define S2DE_KEY_INSERT 77
#define S2DE_KEY_HOME 78
#define S2DE_KEY_PAGE_UP 79
#define S2DE_KEY_PAGE_DOWN 80
#define S2DE_KEY_END 81
#define S2DE_KEY_DELETE 82
#define S2DE_KEY_PRINT_SCREEN 83
#define S2DE_KEY_SCROLL_LOCK 84
#define S2DE_KEY_PAUSE 85
#define S2DE_KEY_MENU 86



namespace S2DE {

	class Input {

	public:
		static bool IsPressed(int key);
		static bool IsHeld(int key);
		static bool IsReleased(int key);


	};

}

#endif