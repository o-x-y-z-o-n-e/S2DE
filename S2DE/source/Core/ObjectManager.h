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

		static void AddObject(Object* object);
		static void RemoveObject(Object* object);
		
		static void StartAllObjects();
		static void DynamicUpdateAllObjects(float delta);
		static void FixedUpdateAllObjects(float delta);
		static void LateUpdateAllObjects(float delta);
		
		static void StartComponents(Object* object);
		static void DynamicUpdateComponents(Object* object, float delta);
		static void FixedUpdateComponents(Object* object, float delta);
		static void LateUpdateComponents(Object* object, float delta);
		
		static void DestroyMarkedObjects();

	public:
		static bool s_hasInit;
		static Object* s_root;

		static std::list<Object*> m_objects;

		static Object* m_objectsToRemove[MAX_OBJECTS];
		static int m_removeObjectCounter;
	};

	

}

#endif