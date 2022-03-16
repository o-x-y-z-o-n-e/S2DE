#include "Collider.h"
#include "ColliderManager.h"
#include "Global.h"

#include <stdio.h>

namespace S2DE {


	void Collider::Init() {
		ColliderManager::Attach(PTR_THIS(Collider));
	}


	Collider::~Collider() {
		ColliderManager::Dettach(PTR_THIS(Collider));
	}


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



	bool Collider::Intersects(std::shared_ptr<Collider> other) {
		rec2f A = GetWorldBounds();
		rec2f B = other->GetWorldBounds();

		bool h = A.x < B.w && A.w > B.x;
		bool v = A.y < B.h && A.h > B.y;
		return h && v;
	}

}