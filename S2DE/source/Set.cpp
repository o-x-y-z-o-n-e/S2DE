#include "Set.h"
#include "Util.h"

namespace S2DE {

	Set::Set(int max) {
		m_data = new void*[max];
		m_max = max;
		m_count = 0;
	}

	Set::~Set() {
		delete(m_data);
	}

	int Set::Max() { return m_max; }
	int Set::Count() { return m_count; }

	void Set::Add(void* data) {
		if (m_count >= m_max)
			return;
		
		int index = FindEmptyIndex(data);

		m_data[index] = data;
		m_count++;
	}

	void* Set::Get(int index) {
		if (index < 0 || index >= m_max)
			return nullptr;

		return m_data[index];
	}

	void Set::Remove(void* data) {
		int index = IndexOf(data);
		if (index < 0) return;

		m_data[index] = nullptr;
		m_count--;
	}

	void* Set::Remove(int index) {
		if (index < 0 || index >= m_max)
			return nullptr;

		void* ptr = m_data[index];

		m_data[index] = nullptr;
		m_count--;

		return ptr;
	}

	bool Set::Contains(void* data) {
		return IndexOf(data) >= 0;
	}

	int Set::IndexOf(void* data) {
		int start = GetPointerHash(data) % m_max;
		int index = start;

		int i = 0;
		while (m_data[index] != nullptr) {
			if (m_data[index] == data)
				return index;

			index = start + (i * i);
		}

		return -1;
	}

	int Set::FindEmptyIndex(void* data) {
		int start = GetPointerHash(data) % m_max;
		int index = start;

		int i = 0;
		while (m_data[index] != nullptr)
			index = start + (i * i);

		return index;
	}

}