#pragma once

namespace S2DE {

	struct vect {
		float x;
		float y;

		vect() { this->x = 0; this->y=0; };
		vect(float x, float y) {
			this->x = x;
			this->y = y;
		};

		static vect zero() { return *new vect(0, 0); };

		vect operator +(const vect& a) {
			vect v = *new vect();
			v.x = x + a.x;
			v.y = y + a.y;

			return v;
		}

		vect operator *(const float a) {
			vect v = *new vect();
			v.x = x * a;
			v.y = y * a;
			return v;
		}

	};

	struct rect {
		float x;
		float y;
		float w;
		float h;

	public:
		rect(float x, float y, float w, float h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
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
