#include "S2DE.h"
#include "Object.h"
#include "Component.h"
#include "ObjectManager.h"

#include <iterator>

namespace S2DE {


	Object::~Object() {
		m_parent->RemoveChild(this);


		for (int i = 0; m_componentCount; i++)
			delete(m_components[i]);
		delete(m_components);


		Object* child = nullptr;
		while ((child = (Object*)m_children.Get(0)) != nullptr) {
			child->~Object();
		}
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
		if (parent == nullptr) return;
		if (ObjectManager::GetRoot() == this)
			return;

		m_parent = parent;
		m_parent->AddChild(this);
	}


	Object* Object::GetParent() { return m_parent; }


	void Object::AddChild(Object* child) {
		if (child->GetParent() != this) {
			child->SetParent(this);
			return;
		}

		m_children.Append(child);
	}


	void Object::RemoveChild(Object* child) { m_children.Remove(child); }


	void Object::Start() {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->Start();

		Chain::Iterator it = m_children.Begin();
		Object* child = nullptr;
		while ((child = (Object*)it.Next()) != nullptr)
			child->Start();
	}

	void Object::DynamicUpdate(float delta) {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->DynamicUpdate(delta);

		Chain::Iterator it = m_children.Begin();
		Object* child = nullptr;
		while ((child = (Object*)it.Next()) != nullptr)
			child->DynamicUpdate(delta);
	}

	void Object::FixedUpdate(float delta) {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->FixedUpdate(delta);

		Chain::Iterator it = m_children.Begin();
		Object* child = nullptr;
		while ((child = (Object*)it.Next()) != nullptr)
			child->FixedUpdate(delta);
	}

	void Object::LateUpdate(float delta) {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->LateUpdate(delta);

		Chain::Iterator it = m_children.Begin();
		Object* child = nullptr;
		while ((child = (Object*)it.Next()) != nullptr)
			child->LateUpdate(delta);
	}


	vec2f Object::GetLocalPosition() { return m_localPosition; }
	vec2f Object::GetWorldPosition() { return m_worldPosition; }

	void Object::SetLocalPosition(vec2f position) {
		m_localPosition = position;

		UpdateWorldPosition();
	}


	void Object::SetWorldPosition(vec2f position) {
		if(m_parent != nullptr)
			m_localPosition = position - m_parent->GetWorldPosition();
		else
			m_localPosition = position;

		UpdateWorldPosition();
	}


	void Object::UpdateWorldPosition() {
		if(m_parent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;

		Chain::Iterator it = m_children.Begin();
		Object* child = nullptr;
		while ((child = (Object*)it.Next()) != nullptr)
			child->UpdateWorldPosition();
	}
}