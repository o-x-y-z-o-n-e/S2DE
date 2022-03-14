#include "Component.h"
#include "Object.h"

namespace S2DE {

	void Component::Init() {}

	void Component::Start() {}

	void Component::DynamicUpdate(float delta) {}

	void Component::LateUpdate(float delta) {}

	void Component::FixedUpdate(float delta) {}

	void Component::AddToObject(std::shared_ptr<Object> object) {
		m_object = object;
		m_object->AddComponent(shared_from_this());
	}

	std::shared_ptr<Object> Component::GetObject() { return m_object; }


	void Component::Dettach() {
		std::shared_ptr<Object> obj = m_object;
		m_object.reset();
		obj->RemoveComponent(shared_from_this());
	}

}