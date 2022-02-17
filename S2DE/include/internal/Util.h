#ifndef UTIL_H
#define UTIL_H

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

	private:
		list_node* GetNode(int i);
		list_node* m_head;
		list_node* m_tail;
		list_node* m_current;
		int m_index;
		int m_count;

	};

}

#endif