#include "Rigidbody.h"
#include "PhysicsManager.h"

#include <math.h>

namespace S2DE {

	void Rigidbody::FixedUpdate(float delta) {
		vec2f position = GetObject()->GetWorldPosition();
		vec2f vel = m_velocity * delta;
		vec2f target = position + vel;
		vec2f size = GetSize();
		vec2f offset = GetOffset();
		vec2f move;
		
		rec2f A = GetWorldBounds();
		rec2f C = { target.x + offset.x,
					   target.y + offset.y,
					   target.x + offset.x + size.x,
					   target.y + offset.y + size.y
		};

		std::list<std::shared_ptr<Collider>> intersections = PhysicsManager::GetIntersectingColliders(C);

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = intersections.begin(); it != intersections.end(); it++) {
			if ((*it).get() != this && !(*it).get()->IsTrigger()) {
				rec2f B = (*it)->GetWorldBounds();
				vec2f d;
				vec2f t;

				if(A.x < B.x) {
					d.x = B.x - A.w;
				} else {
					d.x = A.x - B.w;
				}

				if(A.y < B.y) {
					d.y = B.y - A.h;
				} else {
					d.y = A.y - B.h;
				}

				t.x = vel.x != 0 ? abs(d.x / vel.x) : 0;
				t.y = vel.y != 0 ? abs(d.y / vel.y) : 0;

				float s = 0;

				if(vel.x != 0 && vel.y == 0) {
					s = t.x;
					move.x = s * vel.x;
				} else if (vel.x == 0 && vel.y != 0) {
					s = t.y;
					move.y = s * vel.y;
				} else {
					s = fmin(t.x, t.y);
					move.x = s * vel.x;
					move.y = s * vel.y;
				}

				GetObject()->SetWorldPosition(position + move);
				return;
			}
		}

		GetObject()->SetWorldPosition(target);
	}



	void Rigidbody::SetVelocity(vec2f velocity) { m_velocity = velocity; }
	vec2f Rigidbody::GetVelocity() { return m_velocity; }

}