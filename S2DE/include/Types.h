#ifndef S2DE_TYPES_H
#define S2DE_TYPES_H

#include <stdint.h>
#include <math.h>
#include <memory>

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
		inline float magnitude() { return sqrtf((x*x) + (y*y)); }
		inline vec2f normal() {
			float m = magnitude();
			vec2f n = {x/m, y/m};
			return n;
		}
		

		vec2f operator +(const vec2f& a) {
			vec2f v = { 0.0F, 0.0F };
			v.x = x + a.x;
			v.y = y + a.y;

			return v;
		}

		vec2f& operator +=(const vec2f& a) {
			x += a.x;
			y += a.y;
			return *this;
		}

		vec2f operator -(const vec2f& a) {
			vec2f v = { 0.0F, 0.0F };
			v.x = x - a.x;
			v.y = y - a.y;

			return v;
		}

		vec2f& operator -=(const vec2f& a) {
			x -= a.x;
			y -= a.y;
			return *this;
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

		vec2f& operator *=(const float a) {
			x *= a;
			y *= a;
			return *this;
		}

		vec2f& operator *=(const int a) {
			x *= a;
			y *= a;
			return *this;
		}

		vec2f operator /(const float a) {
			vec2f v = { 0.0F, 0.0F };
			v.x = x * a;
			v.y = y * a;
			return v;
		}

		vec2f operator /(const int a) {
			vec2f v = { 0.0F, 0.0F };
			v.x = x / a;
			v.y = y / a;
			return v;
		}

		vec2f& operator /=(const float a) {
			x /= a;
			y /= a;
			return *this;
		}

		vec2f& operator /=(const int a) {
			x /= a;
			y /= a;
			return *this;
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

		vec2i operator -(const vec2i& a) {
			vec2i v = { 0, 0 };
			v.x = x - a.x;
			v.y = y - a.y;

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


	typedef struct box2f {
		vec2f min;
		vec2f max;
	} box2f;


	typedef struct box2i {
		vec2i min;
		vec2i max;
	} box2i;


	typedef struct ray2f {
		vec2f origin;
		vec2f direction;
		float distance;
		
		inline vec2f start() { return origin; }
		inline vec2f end() { return origin + (direction * distance); }
	} ray2f;


	class Collider;
	typedef struct hitinfo {
		bool hit;
		vec2f point;
		float distance;
		std::shared_ptr<Collider> collider;
	} hitinfo;



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


	class Dictionary {
	private:
		typedef struct Node {
			uint64_t hash;
			void* data;
		} Node;

	public:
		Dictionary();
		Dictionary(int max);
		~Dictionary();

		int Max();
		int Count();

		void Add(void* key, void* data);
		void Add(int key, void* data);
		void Add(const char* key, void* data);
		bool Contains(void* key);
		void* Get(void* key);
		void* Remove(void* key);

	private:
		void Add(uint64_t hash, void* data);
		bool Contains(uint64_t hash);
		void* Get(uint64_t hash);
		void* Remove(uint64_t hash);
		int FindEmptyIndex(uint64_t hash);
		Node* m_data;
		int m_max;
		int m_count;
	};


	//----


	template <typename T>
	class Chain {
	public:
		typedef struct Node {
			T data;
			Node* next;
			Node* prev;
		} Node;

	public:
		typedef struct Iterator {
			Node* current;
			int direction;
			T Next();
		} Iterator;

	public:
		Chain();
		~Chain();

		void Append(const T& data);
		void Insert(int index, const T& data);
		T Get(int index);
		T Pop(int index);
		void Remove(const T& data);
		void Clear();
		Iterator Begin(bool reverse = false);
		int Count();
		bool IsEmpty();


	private:
		int m_count;
		Node* m_head;
		Node* m_tail;
		Node* GetNode(int index);
	};

}

#endif