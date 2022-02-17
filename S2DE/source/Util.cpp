#include "internal/Util.h"
#include <stdlib.h>

namespace S2DE {

	int List::Count() {
		return m_count;
	}


	void List::Add(void* data) {
		list_node* node = (list_node*)malloc(sizeof(list_node));
		if (node == nullptr) return;

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
		if (node == nullptr) return;
		return node->data;
	}


	list_node* List::GetNode(int i) {
		if (m_count == 0)
			return nullptr;
		
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
			while (m_index != i && m_current != nullptr) {
				m_index++;
				m_current = m_current->next;
			}
		} else {
			while (m_index != i && m_current != nullptr) {
				m_index--;
				m_current = m_current->prev;
			}
		}

		return m_current;
	}


	void* List::Remove(int i) {
		list_node* node = GetNode(i);
		if (node == nullptr) return;

		if (i == 0)
			m_head = node->next;
		else if (i == m_count - 1)
			m_tail = node->prev;

		if (node->prev != nullptr) {
			node->prev->next = node->next;

			if (i == m_index) {
				m_current = node->prev;
				m_index--;
			}
		}

		if (node->next != nullptr) {
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
}