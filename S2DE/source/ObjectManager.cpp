#include "internal/ObjectManager.h"
#include "Component.h"

#include <stdlib.h>
#include <string.h>
#include <list>

namespace S2DE {

	std::list<Object*> objects;

	Object* objectsToRemove[MAX_OBJECTS];
	int removeObjectCounter = 0;


	Object* Object::Create(std::string name) {
		Object* object = new Object();
		object->Name = name;

		object->m_components = (Component**)malloc(sizeof(Component**) * MAX_COMPONENTS);
		object->m_componentCount = 0;

		objects.insert(objects.end(), object);
		return object;
	}


	void Object::Destroy(Object* object) {
		for (int i = 0; object->GetComponentCount(); i++)
			delete object->m_components[i];

		free(object->m_components);

		objectsToRemove[removeObjectCounter] = object;
		removeObjectCounter++;
	}



	void DestroyMarkedObjects() {
		for (int i = 0; i < removeObjectCounter; i++) {
			Object* object = objectsToRemove[i];

			objects.remove(object);
			delete object;

			objectsToRemove[i] = nullptr;
		}
		removeObjectCounter = 0;
	}



	void StartAllObjects() {
		std::list<Object*>::iterator it = objects.begin();
		for (it = objects.begin(); it != objects.end(); it++) {
			Object* object = *it;
			StartComponents(object);
		}
	}


	void DynamicUpdateAllObjects(float delta) {
		std::list<Object*>::iterator it = objects.begin();
		for (it = objects.begin(); it != objects.end(); it++) {
			Object* object = *it;
			DynamicUpdateComponents(object, delta);
		}
	}

	void LateUpdateAllObjects(float delta) {
		std::list<Object*>::iterator it = objects.begin();
		for (it = objects.begin(); it != objects.end(); it++) {
			Object* object = *it;
			LateUpdateComponents(object, delta);
		}
	}

	void FixedUpdateAllObjects(float delta) {
		std::list<Object*>::iterator it = objects.begin();
		for (it = objects.begin(); it != objects.end(); it++) {
			Object* object = *it;
			FixedUpdateComponents(object, delta);
		}
	}


	//


	void StartComponents(Object* object) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->Start();
	}

	void DynamicUpdateComponents(Object* object, float delta) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->DynamicUpdate(delta);
	}

	void LateUpdateComponents(Object* object, float delta) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->LateUpdate(delta);
	}

	void FixedUpdateComponents(Object* object, float delta) {
		for (int i = 0; i < object->GetComponentCount(); i++)
			object->GetComponent(i)->FixedUpdate(delta);
	}

}