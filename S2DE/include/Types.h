#ifndef S2DE_TYPES_H
#define S2DE_TYPES_H

namespace S2DE {


	typedef struct vec2f {
		float x;
		float y;

		vec2f() { this->x = 0.0F; this->y = 0.0F; };
		vec2f(float x, float y) {
			this->x = x;
			this->y = y;
		};

		static inline vec2f zero() { return { 0.0F, 0.0F }; }

		vec2f operator +(const vec2f& a) {
			vec2f v = { 0.0F, 0.0F };
			v.x = x + a.x;
			v.y = y + a.y;

			return v;
		}

		vec2f operator *(const float a) {
			vec2f v = { 0.0F, 0.0F };
			v.x = x * a;
			v.y = y * a;
			return v;
		}

		vec2f operator *(const int a) {
			vec2f v = { 0.0F, 0.0F };
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

		static inline vec2i zero() { return { 0, 0 }; }

		vec2i operator +(const vec2i& a) {
			vec2i v = { 0, 0 };
			v.x = x + a.x;
			v.y = y + a.y;

			return v;
		}

		vec2i operator *(const int a) {
			vec2i v = { 0, 0 };
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
			this->x = 0.0F;
			this->y = 0.0F;
			this->w = 0.0F;
			this->h = 0.0F;
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



	//Abstract Data Containers


	class Set {

	public:
		Set(int max);
		~Set();
		int Max();
		int Count();
		void Add(void* data);
		void* Get(int index);
		void Remove(void* data);
		void* Remove(int index);
		bool Contains(void* data);
		int IndexOf(void* data);

	private:
		int FindEmptyIndex(void* data);
		void** m_data;
		int m_max;
		int m_count;

	};


	class Chain {
		void Append(void* data);
		void* Get(int index);
		void Remove(int index);
	private:
		int m_count;

	};


}

#endif