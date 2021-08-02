#include "Component.h"
#include "Object.h"

using namespace S2DE;


void Component::Init() {}

void Component::Start() {}

void Component::Update(float delta) {}

void Component::FixedUpdate(float delta) {}

void Component::Dispose() {}

void Component::AddToObject(Object* object) {
	this->object = object;
	this->object->AddComponent(this);
}

Object* Component::GetObject() { return object; }
