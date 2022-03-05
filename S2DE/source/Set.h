#ifndef S2DE_SET_H
#define S2DE_SET_H

namespace S2DE {

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

}

#endif