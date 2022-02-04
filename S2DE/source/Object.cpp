#include "Object.h"
#include "Component.h"
#include "Core.h"

#include <iterator>

using namespace S2DE;


static std::list<Object*> objects;


void Object::SetPosition(vect position) {
	this->position = position;
}

vect Object::GetPosition() {
	return this->position;
}

void Object::AddComponent(Component* component) {
	if (component->GetObject() == NULL) {
		component->AddToObject(this);
		return;
	}

	//components.insert(components.end(), component);
	components.push_back(component);
	component->Init();

	if (Core::IsRunning()) component->Start();
}


Object* Object::Create(std::string name) {
	Object* object = new Object();
	object->Name = name;
	objects.insert(objects.end(), object);
	return object;
}


void Object::StartAll() {
	std::list<Object*>::iterator it = objects.begin();
	for (it = objects.begin(); it != objects.end(); it++) {
		Object* object = *it;
		object->StartComponents();
	}
}


void Object::DynamicUpdateAll(float delta) {
	std::list<Object*>::iterator it = objects.begin();
	for (it = objects.begin(); it != objects.end(); it++) {
		Object* object = *it;
		object->DynamicUpdateComponents(delta);
	}
}

void Object::LateUpdateAll(float delta) {
	std::list<Object*>::iterator it = objects.begin();
	for (it = objects.begin(); it != objects.end(); it++) {
		Object* object = *it;
		object->LateUpdateComponents(delta);
	}
}

void Object::FixedUpdateAll(float delta) {
	std::list<Object*>::iterator it = objects.begin();
	for (it = objects.begin(); it != objects.end(); it++) {
		Object* object = *it;
		object->FixedUpdateComponents(delta);
	}
}

void Object::DisposeAll() {
	std::list<Object*>::iterator it = objects.begin();
	for (it = objects.begin(); it != objects.end(); it++) {
		Object* object = *it;
		object->Dispose();
	}
}


void Object::StartComponents() {
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++) {
		Component* component = *it;
		component->Start();
  }
}

void Object::DynamicUpdateComponents(float delta) {
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++) {
		Component* component = *it;
		component->DynamicUpdate(delta);
	}
}

void Object::LateUpdateComponents(float delta) {
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++) {
		Component* component = *it;
		component->LateUpdate(delta);
	}
}

void Object::FixedUpdateComponents(float delta) {
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++) {
		Component* component = *it;
		component->FixedUpdate(delta);
	}
}

void Object::Dispose() {
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++) {
		Component* component = *it;
		component->Dispose();
	}
	components.clear();
}
