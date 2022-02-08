#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#define MAX_COMPONENTS 100

#include "Object.h"


namespace S2DE {

	void StartAllObjects();
	void DynamicUpdateAllObjects(float delta);
	void FixedUpdateAllObjects(float delta);
	void LateUpdateAllObjects(float delta);
	
	void StartComponents(Object* object);
	void DynamicUpdateComponents(Object* object, float delta);
	void FixedUpdateComponents(Object* object, float delta);
	void LateUpdateComponents(Object* object, float delta);

}

#endif