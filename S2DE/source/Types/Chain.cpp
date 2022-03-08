#include "Core/Global.h"
#include "Types.h"



namespace S2DE {

	Chain::Chain() {
		m_head = nullptr;
		m_tail = nullptr;
		m_count = 0;
	}


	Chain::~Chain() {
		Clear();
	}

    void Chain::Append(void* data) {
		Node* node = new Node();
		node->data = data;
		
		if (m_count == 0) {
			m_head = node;
			m_tail = node;
		} else {
			m_tail->next = node;
			node->prev = m_tail;
			m_tail = node;
		}

		m_count++;
    }

	void Chain::Insert(int index, void* data) {
		if (index == m_count) {
			Append(data);
			return;
		}

		Node* current = GetNode(index);
		if (current == nullptr) return;
		
		Node* node = new Node();
		node->data = data;

		node->prev = current->prev;
		node->next = current;

		if (current->prev != nullptr)
			current->prev->next = node;

		current->prev = node;
		
		if (index == 0)
			m_head = node;

		m_count++;
	}

    void* Chain::Get(int index) {
		Node* node = GetNode(index);
		if (node == nullptr)
			return nullptr;

		return node->data;
    }

    void* Chain::Remove(int index) {
		Node* node = GetNode(index);
		if (node == nullptr)
			return nullptr;

		if (node->prev != nullptr)
			node->prev->next = node->next;

		if (node->next != nullptr)
			node->next->prev = node->prev;

		if (node == m_head) m_head = node->next;
		if (node == m_tail) m_tail = node->prev;

		void* data = node->data;
		delete(node);
		m_count--;

		return data;
    }


	void Chain::Remove(void* data) {
		Node* current = m_head;
		int i = 0;

		while (current != nullptr) {
			if (current->data == data) {
				Remove(i);
				return;
			}

			current = current->next;
		}
	}


	Chain::Node* Chain::GetNode(int index) {
		if (index < 0 || index >= m_count)
			return nullptr;

		int direction;
		Node* current;
		int i;
		if (m_count - index < index) {
			direction = -1;
			current = m_tail;
			i = m_count - 1;
		} else {
			direction = 1;
			current = m_head;
			i = 0;
		}
		
		while (current != nullptr && i != index) {
			if (direction < 0)
				current = current->prev;
			else
				current = current->next;
		}

		return current;
	}


	Chain::Iterator Chain::Begin(bool reverse) {
		Iterator it;

		if (reverse) {
			it.direction = -1;
			it.current = m_tail;
		} else {
			it.direction = 1;
			it.current = m_head;
		}

		return it;
	}


	void Chain::Clear() {
		while (m_head != nullptr)
			Remove(0);
	}


	void* Chain::Iterator::Next() {
		if (current == nullptr)
			return nullptr;

		Node* node = current;

		if (direction < 0)
			current = current->prev;
		else
			current = current->next;

		return node->data;
	}

}