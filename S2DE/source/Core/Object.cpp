#include "S2DE.h"
#include "Global.h"
#include "Object.h"
#include "Component.h"
#include "ObjectManager.h"

#include <iterator>
#include <type_traits>

namespace S2DE {


	void Object::Dettach() {
		m_parent->RemoveChild(std::shared_ptr<Object>(this));

		while (m_components.size() > 0)
			m_components.front()->Dettach();
		
		while (m_children.size() > 0)
			m_children.front()->Dettach();
	}


	void Object::AddComponent(std::shared_ptr<Component> component) {
		if (component->GetObject().get() == nullptr) {
			component->AddToObject(shared_from_this());
			return;
		} else if (component->GetObject().get() != this)
			return;

		m_components.push_back(component);
		
		component->Init();

		if (S2DE::IsRunning()) component->Start();
	}


	void Object::RemoveComponent(std::shared_ptr<Component> component) {
		if (component->GetObject().get() == this) {
			component->Dettach();
			return;
		}

		m_components.remove(component);
	}


	std::shared_ptr<Component> Object::GetComponent(int i) {
		int c = 0;
		std::list<std::shared_ptr<Component>>::iterator it;
		for (it = m_components.begin(); it != m_components.end(); it++) {
			if (c == i)
				return (*it);
			c++;
		}

		return std::shared_ptr<Component>();
	}

	int Object::GetComponentCount() {
		return m_components.size();
	}


	void Object::SetParent(std::shared_ptr<Object> parent) {
		if (parent.get() == nullptr) return;
		if (ObjectManager::GetRoot().get() == this)
			return;

		// Remove this from old parent.
		if (m_parent.get() != nullptr)
			m_parent->RemoveChild(shared_from_this());
		
		// Assign new parent and attach.
		m_parent = parent;
		m_parent->AddChild(shared_from_this());
	}


	std::shared_ptr<Object> Object::GetParent() { return m_parent; }


	void Object::AddChild(std::shared_ptr<Object> child) {
		if (child->GetParent().get() != this) {
			child->SetParent(shared_from_this());
			return;
		}

		m_children.push_back(child);
	}


	void Object::RemoveChild(std::shared_ptr<Object> child) { m_children.remove(child); }


	void Object::Start() {
		std::list<std::shared_ptr<Component>>::iterator it1;
		for (it1 = m_components.begin(); it1 != m_components.end(); it1++)
			(*it1)->Start();

		std::list<std::shared_ptr<Object>>::iterator it2;
		for (it2 = m_children.begin(); it2 != m_children.end(); it2++)
			(*it2)->Start();
	}

	void Object::DynamicUpdate(float delta) {
		std::list<std::shared_ptr<Component>>::iterator it1;
		for (it1 = m_components.begin(); it1 != m_components.end(); it1++)
			(*it1)->DynamicUpdate(delta);

		std::list<std::shared_ptr<Object>>::iterator it2;
		for (it2 = m_children.begin(); it2 != m_children.end(); it2++)
			(*it2)->DynamicUpdate(delta);
	}

	void Object::FixedUpdate(float delta) {
		std::list<std::shared_ptr<Component>>::iterator it1;
		for (it1 = m_components.begin(); it1 != m_components.end(); it1++)
			(*it1)->FixedUpdate(delta);

		std::list<std::shared_ptr<Object>>::iterator it2;
		for (it2 = m_children.begin(); it2 != m_children.end(); it2++)
			(*it2)->FixedUpdate(delta);
	}

	void Object::LateUpdate(float delta) {
		std::list<std::shared_ptr<Component>>::iterator it1;
		for (it1 = m_components.begin(); it1 != m_components.end(); it1++)
			(*it1)->LateUpdate(delta);

		std::list<std::shared_ptr<Object>>::iterator it2;
		for (it2 = m_children.begin(); it2 != m_children.end(); it2++)
			(*it2)->LateUpdate(delta);
	}


	vec2f Object::GetLocalPosition() { return m_localPosition; }
	vec2f Object::GetWorldPosition() { return m_worldPosition; }

	void Object::SetLocalPosition(vec2f position) {
		m_localPosition = position;

		UpdateWorldPosition();
	}


	void Object::SetWorldPosition(vec2f position) {
		if(m_parent.get() != nullptr)
			m_localPosition = position - m_parent->GetWorldPosition();
		else
			m_localPosition = position;

		UpdateWorldPosition();
	}


	void Object::UpdateWorldPosition() {
		if(m_parent.get() == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;

		std::list<std::shared_ptr<Object>>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
			(*it)->UpdateWorldPosition();
	}
}