#ifndef S2DE_COMPONENT_H
#define S2DE_COMPONENT_H

namespace S2DE {

    class Object;

    class Component {

	public:
		Object* GetObject();
		void AddToObject(Object* object);
		virtual void Init();
		virtual void Start();
		virtual void DynamicUpdate(float delta);
		virtual void LateUpdate(float delta);
		virtual void FixedUpdate(float delta);

	private:
		Object* m_object;

	};
}

#endif