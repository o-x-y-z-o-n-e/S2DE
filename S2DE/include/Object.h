#ifndef S2DE_OBJECT_H
#define S2DE_OBJECT_H

#include "Types.h"
#include <string>

namespace S2DE {

    class Component;

    class Object {

	public:
		std::string Name;
		void SetPosition(vec2f position);
		vec2f GetPosition();
		void AddComponent(Component* component);
		Component* GetComponent(int i);
		int GetComponentCount();
		void SetParent(Object* parent);
		Object* GetParent();
		void AddChild(Object* child);

	private:
		Object() {}
		vec2f m_position;
		Component** m_components;
		int m_componentCount;

		Object* m_parent;
		Chain m_children;

	public:
		static Object* Create(std::string name, Object* parent = nullptr);
		static void Destroy(Object* object);

	};

}

#endif