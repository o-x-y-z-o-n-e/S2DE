#ifndef S2DE_COLLIDER_H
#define S2DE_COLLIDER_H\

#include "Component.h"

namespace S2DE {

	class Collider : public Component {

	public:
		vec2f GetSize();
		vec2f GetOffset();

		void SetSize(vec2f size);
		void SetOffset(vec2f offset);

		rec2f GetLocalBounds();
		rec2f GetWorldBounds();

		void SetTrigger(bool trigger);
		bool IsTrigger();

	private:
		vec2f m_size;
		vec2f m_offset;
		bool m_isTrigger; //IMPLEMENT

	};

}

#endif