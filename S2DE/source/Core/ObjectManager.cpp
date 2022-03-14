#include "ObjectManager.h"
#include "Component.h"

#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <memory>

namespace S2DE {

	bool ObjectManager::s_hasInit;
	std::shared_ptr<Object> ObjectManager::s_root;
	std::shared_ptr<Object> ObjectManager::s_objectsToRemove[MAX_OBJECTS];
	int ObjectManager::s_removeObjectCounter;


	void ObjectManager::Init() {
		if (s_hasInit)
			return;

		s_root = Object::Create("Root");

		s_hasInit = true;
	}


	std::shared_ptr<Object> Object::Create(std::string name, std::shared_ptr<Object> parent) {
		std::shared_ptr<Object> object = std::make_shared<Object>();
		object->Name = name;

		if (parent.get() == nullptr) {
			if (ObjectManager::GetRoot().get() != nullptr)
				object->SetParent(ObjectManager::GetRoot());
		} else {
			object->SetParent(parent);
		}

		return object;
	}


	void Object::Destroy(std::shared_ptr<Object> object) {
		if (object == ObjectManager::GetRoot())
			return;

		ObjectManager::RemoveObject(object);
	}


	void ObjectManager::RemoveObject(std::shared_ptr<Object> object) {
		s_objectsToRemove[s_removeObjectCounter] = object;
		s_removeObjectCounter++;
	}


	void ObjectManager::DestroyMarkedObjects() {
		for (int i = 0; i < s_removeObjectCounter; i++) {
			std::shared_ptr<Object> object = s_objectsToRemove[i];

			if (object.get() != nullptr)
				object.reset();
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



	std::shared_ptr<Object> ObjectManager::GetRoot() { return s_root; }

}