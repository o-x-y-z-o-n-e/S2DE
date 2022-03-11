#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#define MAX_OBJECTS 10000
#define MAX_COMPONENTS 100

#include "Object.h"
#include <list>

namespace S2DE {


	class ObjectManager {

	public:
		static void Init();

		static Object* GetRoot();

		static void StartAllObjects();
		static void DynamicUpdateAllObjects(float delta);
		static void FixedUpdateAllObjects(float delta);
		static void LateUpdateAllObjects(float delta);
		
		static void RemoveObject(Object* object);
		static void DestroyMarkedObjects();

	public:
		static bool s_hasInit;
		static Object* s_root;

		static Object* s_objectsToRemove[MAX_OBJECTS];
		static int s_removeObjectCounter;
	};

	

}

#endif