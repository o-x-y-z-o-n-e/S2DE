#include "ObjectManager.h"
#include "Component.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

namespace S2DE {

	bool ObjectManager::s_hasInit;
	Object* ObjectManager::s_root;
	Object* ObjectManager::s_objectsToRemove[MAX_OBJECTS];
	int ObjectManager::s_removeObjectCounter;


	void ObjectManager::Init() {
		if (s_hasInit)
			return;

		s_root = Object::Create("Root");

		s_hasInit = true;
	}


	Object* Object::Create(std::string name, Object* parent) {
		Object* object = new Object();
		object->Name = name;

		object->m_components = new Component*[MAX_COMPONENTS];
		object->m_componentCount = 0;

		if (parent == nullptr) {
			if (ObjectManager::GetRoot() != nullptr)
				object->SetParent(ObjectManager::GetRoot());
		} else {
			object->SetParent(parent);
		}

		return object;
	}


	void Object::Destroy(Object* object) {
		if (object == ObjectManager::GetRoot())
			return;

		ObjectManager::RemoveObject(object);
	}


	void ObjectManager::RemoveObject(Object* object) {
		s_objectsToRemove[s_removeObjectCounter] = object;
		s_removeObjectCounter++;
	}


	void ObjectManager::DestroyMarkedObjects() {
		for (int i = 0; i < s_removeObjectCounter; i++) {
			Object* object = s_objectsToRemove[i];

			if(object != nullptr)
				delete(object);

			s_objectsToRemove[i] = nullptr;
		}
		s_removeObjectCounter = 0;
	}


	void ObjectManager::StartAllObjects() {
		s_root->Start();
	}

	void ObjectManager::DynamicUpdateAllObjects(float delta) {
		s_root->DynamicUpdate(delta);
	}

	void ObjectManager::LateUpdateAllObjects(float delta) {
		s_root->FixedUpdate(delta);
	}

	void ObjectManager::FixedUpdateAllObjects(float delta) {
		s_root->LateUpdate(delta);
	}



	Object* ObjectManager::GetRoot() { return s_root; }

}