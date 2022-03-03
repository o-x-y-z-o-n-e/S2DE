#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>

namespace S2DE {

	struct list_node;
	typedef struct list_node {
		struct list_node* prev;
		struct list_node* next;
		void* data;
	} list_node;


	//


	class List {

	public:
		int Count();
		void Add(void* data);
		void* Get(int i);
		void* Remove(int i);
		bool Contains(void* data);

	private:
		list_node* GetNode(int i);
		list_node* m_head;
		list_node* m_tail;
		list_node* m_current;
		int m_index;
		int m_count;

	};


	int16_t BytesToInt16(uint8_t* buffer);
	uint16_t BytesToUInt16(uint8_t* buffer);
	int32_t BytesToInt32(uint8_t* buffer);
	uint32_t BytesToUInt32(uint8_t* buffer);

}

#endif