#include "S2DE.h"
#include "Object.h"
#include "Component.h"
#include "ObjectManager.h"

#include <iterator>

namespace S2DE {


	Object::~Object() {
		m_parent->RemoveChild(this);


		for (int i = 0; m_componentCount; i++)
			m_components[i].reset();
		delete(m_components);

		while (m_children.size() > 0) {
			m_children.front()->~Object();
			//m_children.pop_back();
		}
	}

	void Object::AddComponent(std::shared_ptr<Component> component) {
		if (component->GetObject() == nullptr) {
			component->AddToObject(this);
			return;
		}

		m_components[m_componentCount] = component;
		m_componentCount++;
		
		component->Init();

		if (S2DE::IsRunning()) component->Start();
	}


	std::shared_ptr<Component> Object::GetComponent(int i) {
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

		m_children.push_back(child);
	}


	void Object::RemoveChild(Object* child) { m_children.remove(child); }


	void Object::Start() {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->Start();

		std::list<Object*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
			(*it)->Start();
	}

	void Object::DynamicUpdate(float delta) {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->DynamicUpdate(delta);

		std::list<Object*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
			(*it)->DynamicUpdate(delta);
	}

	void Object::FixedUpdate(float delta) {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->FixedUpdate(delta);

		std::list<Object*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
			(*it)->FixedUpdate(delta);
	}

	void Object::LateUpdate(float delta) {
		for (int i = 0; i < m_componentCount; i++)
			m_components[i]->LateUpdate(delta);

		std::list<Object*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
			(*it)->LateUpdate(delta);
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

		std::list<Object*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
			(*it)->UpdateWorldPosition();
	}
}