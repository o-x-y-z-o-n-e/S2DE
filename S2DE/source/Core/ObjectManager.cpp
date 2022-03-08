#include "ObjectManager.h"
#include "Component.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

namespace S2DE {

	std::list<Object*> ObjectManager::m_objects;
	Object* ObjectManager::m_objectsToRemove[MAX_OBJECTS];
	int ObjectManager::m_removeObjectCounter;


	void ObjectManager::Init() {
		if (s_hasInit)
			return;

		s_root = Object::Create("Root");

		s_hasInit = true;
	}


	Object* Object::Create(std::string name, Object* parent = nullptr) {
		Object* object = new Object();
		object->Name = name;

		object->m_components = new Component*[MAX_COMPONENTS];
		object->m_componentCount = 0;

		ObjectManager::AddObject(object);

		return object;
	}


	void Object::Destroy(Object* object) {
		for (int i = 0; object->GetComponentCount(); i++)
			delete(object->m_components[i]);

		delete(object->m_components);

		m_children.~Chain();

		ObjectManager::RemoveObject(object);
	}


	void ObjectManager::AddObject(Object* object) {
		if (s_root == nullptr) {
			s_root = object;
		}

		m_objects.insert(m_objects.end(), object);
	}


	void ObjectManager::RemoveObject(Object* object) {
		m_objectsToRemove[m_removeObjectCounter] = object;
		m_removeObjectCounter++;
	}


	void ObjectManager::DestroyMarkedObjects() {
		for (int i = 0; i < m_removeObjectCounter; i++) {
			Object* object = m_objectsToRemove[i];

			m_objects.remove(object);
			delete object;

			m_objectsToRemove[i] = NULL;
		}
		m_removeObjectCounter = 0;
	}


	void ObjectManager::StartAllObjects() {
		std::list<Object*>::iterator it = m_objects.begin();
		for (it = m_objects.begin(); it != m_objects.end(); it++) {
			Object* object = *it;
			StartComponents(object);
		}
	}


	void ObjectManager::DynamicUpdateAllObjects(float delta) {
		std::list<Object*>::iterator it = m_objects.begin();
		for (it = m_objects.begin(); it != m_objects.end(); it++) {
			Object* object = *it;
			DynamicUpdateComponents(object, delta);
		}
	}

	void ObjectManager::LateUpdateAllObjects(float delta) {
		std::list<Object*>::iterator it = m_objects.begin();
		for (it = m_objects.begin(); it != m_objects.end(); it++) {
			Object* object = *it;
			LateUpdateComponents(object, delta);
		}
	}

	void ObjectManager::FixedUpdateAllObjects(float delta) {
		std::list<Object*>::iterator it = m_objects.begin();
		for (it = m_objects.begin(); it != m_objects.end(); it++) {
			Object* object = *it;
			FixedUpdateComponents(object, delta);
		}
	}


	//


	void ObjectManager::StartComponents(Object* object) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->Start();
	}

	void ObjectManager::DynamicUpdateComponents(Object* object, float delta) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->DynamicUpdate(delta);
	}

	void ObjectManager::LateUpdateComponents(Object* object, float delta) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->LateUpdate(delta);
	}

	void ObjectManager::FixedUpdateComponents(Object* object, float delta) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->FixedUpdate(delta);
	}

}