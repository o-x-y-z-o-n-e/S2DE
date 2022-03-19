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
				
				vec2f diff = Resolve(A, B, vel);

				GetObject()->SetWorldPosition(position + diff);
				return;
			}
		}

		GetObject()->SetWorldPosition(target);
	}


	vec2f Rigidbody::Resolve(const rec2f& A, const rec2f& B, const vec2f& v) {
		vec2f d;
		vec2f t;

		vec2f move;
		vec2f slide;

		if (A.x < B.x) {
			d.x = B.x - A.w;
		} else {
			d.x = A.x - B.w;
		}

		if (A.y < B.y) {
			d.y = B.y - A.h;
		} else {
			d.y = A.y - B.h;
		}

		t.x = v.x != 0 ? abs(d.x / v.x) : 0;
		t.y = v.y != 0 ? abs(d.y / v.y) : 0;

		float s = 0;

		if (v.x != 0 && v.y == 0) {
			s = t.x;
			move.x = s * v.x;
		} else if (v.x == 0 && v.y != 0) {
			s = t.y;
			move.y = s * v.y;
		} else {
			s = fmin(t.x, t.y);
			move.x = s * v.x;
			move.y = s * v.y;

			// CHECK FOR SLIDE COLLISION
			if (s == t.x) slide.y = v.y - move.y;
			if (s == t.y) slide.x = v.x - move.x;
		}

		return move + slide;
	}


	void Rigidbody::SetVelocity(vec2f velocity) { m_velocity = velocity; }
	vec2f Rigidbody::GetVelocity() { return m_velocity; }

}