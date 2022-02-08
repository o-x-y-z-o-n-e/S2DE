#ifndef S2DE_TYPES_H
#define S2DE_TYPES_H

namespace S2DE {


	typedef struct vec2f {
		float x;
		float y;

		vec2f() { this->x = 0; this->y = 0; };
		vec2f(float x, float y) {
			this->x = x;
			this->y = y;
		};

		static vec2f zero() { return *new vec2f(0, 0); };

		vec2f operator +(const vec2f& a) {
			vec2f v = *new vec2f();
			v.x = x + a.x;
			v.y = y + a.y;

			return v;
		}

		vec2f operator *(const float a) {
			vec2f v = *new vec2f();
			v.x = x * a;
			v.y = y * a;
			return v;
		}

	} vec2f;


	//


	typedef struct vec2i {
		int x;
		int y;

		vec2i() { this->x = 0; this->y = 0; };
		vec2i(int x, int y) {
			this->x = x;
			this->y = y;
		};

		static vec2i zero() { return *new vec2i(0, 0); };

		vec2i operator +(const vec2i& a) {
			vec2i v = *new vec2i();
			v.x = x + a.x;
			v.y = y + a.y;

			return v;
		}

		vec2i operator *(const int a) {
			vec2i v = *new vec2i();
			v.x = x * a;
			v.y = y * a;
			return v;
		}

	} vec2i;


	//


	typedef struct rec2f {
		float x;
		float y;
		float w;
		float h;

	public:
		rec2f() {
			this->x = 0;
			this->y = 0;
			this->w = 0;
			this->h = 0;
		}

		rec2f(float x, float y, float w, float h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	} rec2f;


	//


	typedef struct rec2i {
		int x;
		int y;
		int w;
		int h;

	public:
		rec2i() {
			this->x = 0;
			this->y = 0;
			this->w = 0;
			this->h = 0;
		}

		rec2i(int x, int y, int w, int h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	} rec2i;
}

#endif