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
		void SetPosition(Vector position);
		Vector GetPosition();
		void AddComponent(Component* component);

	private:
		Vector position;
		std::list<Component*> components;
		void StartComponents();
		void UpdateComponents(float delta);
		void Dispose();

	public:
		static Object* Create(std::string name);
		static void StartAll();
		static void UpdateAll(float delta);
		static void DisposeAll();

	};

}
