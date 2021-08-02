#pragma once

namespace S2DE {

	struct Vector {
		float x;
		float y;

	public:
		Vector() { this->x = 0; this->y=0; };
		Vector(float x, float y) {
			this->x = x;
			this->y = y;
		};
	};


	class Core {

	public:
		static int Init();
		static void Start();
		static void Close();
		static bool IsRunning();

	private:
		Core() {}
		static void Loop();

	};


	/*
	class Component;
	class Object;
	class Window;
	class Sprite;
	class Texture;
	class Input;*/

}
