#ifndef S2DE_OBJECT_H
#define S2DE_OBJECT_H

#include "Types.h"
#include <string>
#include <list>

namespace S2DE {

    class Component;

    class Object {

	public:
		~Object(); // make private somehow

		std::string Name;
		void AddComponent(Component* component);
		Component* GetComponent(int i);
		int GetComponentCount();
		void SetParent(Object* parent);
		Object* GetParent();
		void AddChild(Object* child);

		void Start();
		void DynamicUpdate(float delta);
		void FixedUpdate(float delta);
		void LateUpdate(float delta);

		vec2f GetLocalPosition();
		vec2f GetWorldPosition();
		void SetLocalPosition(vec2f position);
		void SetWorldPosition(vec2f position);

	private:
		Object() {}
		
		void RemoveChild(Object* child);
		void UpdateWorldPosition();

		vec2f m_localPosition;
		vec2f m_worldPosition;

		Object* m_parent;
		std::list<Object*> m_children;

		Component** m_components;
		int m_componentCount;

	public:
		static Object* Create(std::string name, Object* parent = nullptr);
		static void Destroy(Object* object);

	};

}

#endif