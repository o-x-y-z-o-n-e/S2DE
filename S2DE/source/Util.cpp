#include "Util.h"
#include <string>
#include <stdlib.h>
#include <stddef.h>

namespace S2DE {

	int List::Count() {
		return m_count;
	}


	void List::Add(void* data) {
		list_node* node = (list_node*)malloc(sizeof(list_node));
		if (node == NULL) return;

		node->data = data;

		if (m_count == 0) {
			m_head = node;
		} else {
			node->prev = m_tail;
			m_tail->next = node;
		}

		m_tail = node;
		m_current = node;

		m_index = m_count;
		m_count++;
	}


	void* List::Get(int i) {
		list_node* node = GetNode(i);
		if (node == NULL) return NULL;
		return node->data;
	}


	list_node* List::GetNode(int i) {
		if (m_count == 0)
			return NULL;
		
		int start = i;
		int cur = abs(m_index - i);
		int end = -(m_count - i);
		
		bool inc = true;

		if (cur < start && cur < end) {
			inc = m_index - i > 0;
		} else if(start < end) {
			inc = true;
			m_index = 0;
			m_current = m_head;
		} else {
			inc = false;
			m_index = m_count - 1;
			m_current = m_tail;
		}

		if (inc) {
			while (m_index != i && m_current != NULL) {
				m_index++;
				m_current = m_current->next;
			}
		} else {
			while (m_index != i && m_current != NULL) {
				m_index--;
				m_current = m_current->prev;
			}
		}

		return m_current;
	}


	bool List::Contains(void* data) {
		if(m_count == 0)
			return false;
		
		list_node* current = m_head;
		while(current != NULL) {
			if(current->data == data)
				return true;
		}

		return false;
	}


	void* List::Remove(int i) {
		list_node* node = GetNode(i);
		if (node == NULL) return NULL;

		if (i == 0)
			m_head = node->next;
		else if (i == m_count - 1)
			m_tail = node->prev;

		if (node->prev != NULL) {
			node->prev->next = node->next;

			if (i == m_index) {
				m_current = node->prev;
				m_index--;
			}
		}

		if (node->next != NULL) {
			node->next->prev = node->prev;

			if (i == m_index) {
				m_current = node->next;
				m_index++;
			}
		}

		m_count--;

		void* data = node->data;

		free(node);

		return data;
	}


	//=====


	int GetStringHash(std::string s) {
		return 0;
	}



	int16_t BytesToInt16(u_int8_t* buffer) {
		int16_t value = 0;

		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}


	u_int16_t BytesToUInt16(u_int8_t* buffer) {
		u_int16_t value = 0;

		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}



	int32_t BytesToInt32(u_int8_t* buffer) {
		int32_t value = 0;

		value = (value << 8) + buffer[3];
		value = (value << 8) + buffer[2];
		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}


	u_int32_t BytesToUInt32(u_int8_t* buffer) {
		u_int32_t value = 0;

		value = (value << 8) + buffer[3];
		value = (value << 8) + buffer[2];
		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}



}