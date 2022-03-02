#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <stdbool.h>
#include <stdint.h>

namespace S2DE {

	#ifdef S2DE_WINDOWS
	typedef uint8_t u_int8_t;
	typedef uint16_t u_int16_t;
	typedef uint32_t u_int32_t;
	#endif

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


	int GetStringHash(std::string s);


	int16_t BytesToInt16(u_int8_t* buffer);
	u_int16_t BytesToUInt16(u_int8_t* buffer);
	int32_t BytesToInt32(u_int8_t* buffer);
	u_int32_t BytesToUInt32(u_int8_t* buffer);

}

#endif