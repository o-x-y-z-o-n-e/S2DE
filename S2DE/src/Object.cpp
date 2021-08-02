#include "Object.h"
#include "Component.h"
#include "Core.h"

#include <iterator>

using namespace S2DE;


static std::list<Object*> objects;


void Object::SetPosition(Vector position) {
	this->position = position;
}

Vector Object::GetPosition() {
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


void Object::UpdateAll(float delta) {
	std::list<Object*>::iterator it = objects.begin();
	for (it = objects.begin(); it != objects.end(); it++) {
		Object* object = *it;
		object->UpdateComponents(delta);
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

void Object::UpdateComponents(float delta) {
	std::list<Component*>::iterator it;
	for (it = components.begin(); it != components.end(); it++) {
		Component* component = *it;
		component->Update(delta);
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
