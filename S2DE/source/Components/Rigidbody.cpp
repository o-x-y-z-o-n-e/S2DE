#include "Rigidbody.h"
#include "PhysicsManager.h"

namespace S2DE {

	void Rigidbody::FixedUpdate(float delta) {
		vec2f position = GetObject()->GetWorldPosition();
		vec2f direction = m_velocity * delta;
		vec2f target = position + direction;

		vec2f size = GetSize();
		vec2f offset = GetOffset();
		
		rec2f area = { target.x + offset.x,
					   target.y + offset.y,
					   target.x + offset.x + size.x,
					   target.y + offset.y + size.y
		};

		std::list<std::shared_ptr<Collider>> intersections = PhysicsManager::GetIntersectingColliders(area);

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = intersections.begin(); it != intersections.end(); it++) {
			if ((*it).get() != this) {
				return;
			}
		}

		GetObject()->SetWorldPosition(target);
	}



	void Rigidbody::SetVelocity(vec2f velocity) { m_velocity = velocity; }
	vec2f Rigidbody::GetVelocity() { return m_velocity; }

}