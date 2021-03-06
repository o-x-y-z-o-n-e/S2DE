#include "Core/Global.h"
#include "Types.h"



namespace S2DE {

	template<typename T>
	Chain<T>::Chain() {
		m_head = nullptr;
		m_tail = nullptr;
		m_count = 0;
	}

	template<typename T>
	Chain<T>::~Chain() {
		Clear();
	}

	template<typename T>
    void Chain<T>::Append(const T& data) {
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

	template<typename T>
	void Chain<T>::Insert(int index, const T& data) {
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

	template<typename T>
    T Chain<T>::Get(int index) {
		Node* node = GetNode(index);
		if (node == nullptr)
			return nullptr;

		return node->data;
    }

	template<typename T>
    T Chain<T>::Pop(int index) {
		Node* node = GetNode(index);
		if (node == nullptr)
			return nullptr;

		if (node->prev != nullptr)
			node->prev->next = node->next;

		if (node->next != nullptr)
			node->next->prev = node->prev;

		if (node == m_head) m_head = node->next;
		if (node == m_tail) m_tail = node->prev;

		T data = node->data;
		delete(node);
		m_count--;

		return data;
    }


	template<typename T>
	void Chain<T>::Remove(const T& data) {
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


	template<typename T>
	typename Chain<T>::Node* Chain<T>::GetNode(int index) {
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


	template<typename T>
	typename Chain<T>::Iterator Chain<T>::Begin(bool reverse) {
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


	template<typename T>
	void Chain<T>::Clear() {
		while (m_head != nullptr)
			Remove(0);
	}


	template<typename T>
	T Chain<T>::Iterator::Next() {
		if (current == nullptr)
			return nullptr;

		Node* node = current;

		if (direction < 0)
			current = current->prev;
		else
			current = current->next;

		return node->data;
	}


	template<typename T>
	int Chain<T>::Count() { return m_count; }

	template<typename T>
	bool Chain<T>::IsEmpty() { return m_count == 0; }

}