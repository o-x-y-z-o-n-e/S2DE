#include "S2DE.h"
#include "Object.h"
#include "Component.h"

#include <iterator>

namespace S2DE {

	void Object::SetPosition(vec2f position) {
		this->m_position = position;
	}

	vec2f Object::GetPosition() {
		return this->m_position;
	}

	void Object::AddComponent(Component* component) {
		if (component->GetObject() == NULL) {
			component->AddToObject(this);
			return;
		}

		m_components[m_componentCount] = component;
		m_componentCount++;
		
		component->Init();

		if (S2DE::IsRunning()) component->Start();
	}


	Component* Object::GetComponent(int i) {
		return m_components[i];
	}


	int Object::GetComponentCount() {
		return m_componentCount;
	}


	void Object::SetParent(Object* parent) {
		m_parent = parent;
		m_parent->AddChild(this);
	}


	Object* GetParent() { return m_parent; }


	void Object::AddChild(Object* child) {
		if (child->GetParent() != this) {
			child->SetParent(this);
			return;
		}

		//add child
	}
}