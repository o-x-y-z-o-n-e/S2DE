#ifndef S2DE_OBJECT_H
#define S2DE_OBJECT_H

#include "Types.h"
#include <string>

namespace S2DE {

    class Component;

    class Object {

	public:
		Object() {}

		std::string Name;
		void SetPosition(vec2f position);
		vec2f GetPosition();
		void AddComponent(Component* component);
		Component* GetComponent(int i);
		int GetComponentCount();

	private:
		vec2f m_position;
		Component** m_components = nullptr;
		int m_componentCount = 0;

	public:
		static Object* Create(std::string name);
		static void Destroy(Object* object);

	};

}

#endif