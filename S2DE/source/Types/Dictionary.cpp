#include "Types.h"
#include "Core/Util.h"

namespace S2DE {

	Dictionary::Dictionary() {
		m_data = nullptr;
		m_max = 0;
		m_count = 0;
	}

	Dictionary::Dictionary(int max) {
		m_data = new Node[max];
		m_max = max;
		m_count = 0;
	}

	Dictionary::~Dictionary() {
		if(m_data != nullptr)
			delete(m_data);
	}

	int Dictionary::Max() { return m_max; }
	int Dictionary::Count() { return m_count; }
	

	void Dictionary::Add(int key, void* data) {}
	void Dictionary::Add(const char* key, void* data) {}

	void Dictionary::Add(void* key, void* data) { Add(Hash(key), data); }
	bool Dictionary::Contains(void* key) { return Contains(Hash(key)); }
	void* Dictionary::Get(void* key) { return Get(Hash(key)); }
	void* Dictionary::Remove(void* key) { return Remove(Hash(key)); }



	void Dictionary::Add(uint64_t hash, void* data) {
		int index = FindEmptyIndex(hash);
		if (index < 0) return;

		m_data[index].hash = hash;
		m_data[index].data = data;
		m_count++;
	}


	bool Dictionary::Contains(uint64_t hash) {
		int start = hash % m_max;
		int index = start;
		int i = 0;
		while (m_data[index].data != nullptr) {
			if (m_data[index].hash == hash)
				return true;

			i++;
			index = start + (i * i);
		}

		return false;
	}


	void* Dictionary::Get(uint64_t hash) {
		int start = hash % m_max;
		int index = start;
		int i = 0;
		while (m_data[index].data != nullptr) {
			if (m_data[index].hash == hash)
				return m_data[index].data;

			i++;
			index = start + (i * i);
		}

		return nullptr;
	}


	void* Dictionary::Remove(uint64_t hash) {
		int start = hash % m_max;
		int index = start;
		int i = 0;
		while (m_data[index].data != nullptr) {
			if (m_data[index].hash == hash) {
				void* data = m_data[index].data;
				m_data[index].hash = 0;
				m_data[index].data = nullptr;
				return data;
			}

			i++;
			index = start + (i * i);
		}

		return nullptr;
	}

	
	int Dictionary::FindEmptyIndex(uint64_t hash) {
		int start = hash % m_max;
		int index = start;
		int i = 0;
		while (m_data[index].data != nullptr) {
			if (m_data[index].hash == hash)
				return -1; // Already exists in table

			i++;
			index = start + (i * i);
		}
		return index;
	}

}