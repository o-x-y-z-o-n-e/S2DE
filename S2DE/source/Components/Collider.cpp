#include "Collider.h"

namespace S2DE {

	void Collider::SetSize(vec2f size) { m_size = size; }
	void Collider::SetOffset(vec2f offset) { m_offset = offset; }
	vec2f Collider::GetSize() { return m_size; }
	vec2f Collider::GetOffset() { return m_offset; }
	void Collider::SetTrigger(bool trigger) { m_isTrigger = trigger; }
	bool Collider::IsTrigger() { return m_isTrigger; }


	rec2f Collider::GetLocalBounds() {
		return { m_offset.x,
				 m_offset.y,
				 m_offset.x + m_size.x,
				 m_offset.y + m_size.y
		};
	}

	rec2f Collider::GetWorldBounds() {
		vec2f p = GetObject()->GetWorldPosition();
		return { p.x + m_offset.x,
				 p.y + m_offset.y,
				 p.x + m_offset.x + m_size.x,
				 p.y + m_offset.y + m_size.y
		};
	}

}