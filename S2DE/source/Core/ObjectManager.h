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

		static std::shared_ptr<Object> GetRoot();

		static void StartAllObjects();
		static void DynamicUpdateAllObjects(float delta);
		static void FixedUpdateAllObjects(float delta);
		static void LateUpdateAllObjects(float delta);
		
		static void RemoveObject(std::shared_ptr<Object> object);
		static void DestroyMarkedObjects();

	public:
		static bool s_hasInit;
		static std::shared_ptr<Object> s_root;

		static std::shared_ptr<Object> s_objectsToRemove[MAX_OBJECTS];
		static int s_removeObjectCounter;
	};

	

}

#endif