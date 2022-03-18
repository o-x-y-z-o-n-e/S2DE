#ifndef S2DE_OBJECT_H
#define S2DE_OBJECT_H

#include "Types.h"
#include "Application.h"
#include <string>
#include <list>
#include <memory>

namespace S2DE {

    class Component;
	class Object;

    class Object : public std::enable_shared_from_this<Object> {

	public:
		void Dettach();

		std::string Name;

		void AddComponent(std::shared_ptr<Component> component);
		void RemoveComponent(std::shared_ptr<Component> component);
		std::shared_ptr<Component> GetComponent(int i);
		int GetComponentCount();

		template<class T> inline std::shared_ptr<T> CreateComponent() {
			if constexpr (!std::is_base_of<Component, T>::value) {
				LogError("Type passed is not a derivative of Component!");
				return nullptr;
			}

			std::shared_ptr<T> comp = std::make_shared<T>();

			AddComponent(comp);

			return comp;
		}


		void SetParent(std::shared_ptr<Object> parent);
		std::shared_ptr<Object> GetParent();
		void AddChild(std::shared_ptr<Object> child);

		void Start();
		void DynamicUpdate(float delta);
		void FixedUpdate(float delta);
		void LateUpdate(float delta);

		vec2f GetLocalPosition();
		vec2f GetWorldPosition();
		void SetLocalPosition(vec2f position);
		void SetWorldPosition(vec2f position);

	private:
		void RemoveChild(std::shared_ptr<Object> child);
		void UpdateWorldPosition();

		vec2f m_localPosition;
		vec2f m_worldPosition;

		std::shared_ptr<Object> m_parent;
		std::list<std::shared_ptr<Object>> m_children;
		std::list<std::shared_ptr<Component>> m_components;

	public:
		static std::shared_ptr<Object> Create(std::string name, std::shared_ptr<Object> parent = nullptr);
		static void Destroy(std::shared_ptr<Object> object);

	};

}

#endif