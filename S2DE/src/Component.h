#pragma once

namespace S2DE {

    class Object;

    class Component {

	public:
		Object* GetObject();
		void AddToObject(Object* object);
		virtual void Init();
		virtual void Start();
		virtual void Update(float delta);
		virtual void FixedUpdate(float delta);
		virtual void Dispose();

	private:
		Object* object;

	};
}
