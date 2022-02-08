#include "Component.h"
#include "Object.h"

namespace S2DE {

	void Component::Init() {}

	void Component::Start() {}

	void Component::DynamicUpdate(float delta) {}

	void Component::LateUpdate(float delta) {}

	void Component::FixedUpdate(float delta) {}

	void Component::AddToObject(Object* object) {
		m_object = object;
		m_object->AddComponent(this);
	}

	Object* Component::GetObject() { return m_object; }

}