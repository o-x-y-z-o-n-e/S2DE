#ifndef S2DE_COMPONENT_H
#define S2DE_COMPONENT_H

#include "Object.h"
#include <memory>

namespace S2DE {

	class Component;

    class Component : public std::enable_shared_from_this<Component> {

	public:
		void Dettach();

		std::shared_ptr<Object> GetObject();
		void AddToObject(std::shared_ptr<Object> object);
		virtual void Init();
		virtual void Start();
		virtual void DynamicUpdate(float delta);
		virtual void LateUpdate(float delta);
		virtual void FixedUpdate(float delta);

	private:
		std::shared_ptr<Object> m_object;

	};
}

#endif