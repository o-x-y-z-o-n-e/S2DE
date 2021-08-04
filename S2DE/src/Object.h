#pragma once

#include "Core.h"
#include <string>
#include <list>

namespace S2DE {

    class Component;

    class Object {

	public:
		std::string Name;
		Object() {}
		void SetPosition(vect position);
		vect GetPosition();
		void AddComponent(Component* component);

        //template <class T>
        //T* GetComponent(T value);

	private:
		vect position;
		std::list<Component*> components;
		void StartComponents();
		void DynamicUpdateComponents(float delta);
        void FixedUpdateComponents(float delta);
		void LateUpdateComponents(float delta);
		void Dispose();

	public:
		static Object* Create(std::string name);
		static void StartAll();
		static void DynamicUpdateAll(float delta);
        static void FixedUpdateAll(float delta);
		static void LateUpdateAll(float delta);
		static void DisposeAll();

	};

}
