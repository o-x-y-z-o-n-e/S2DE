#include "Rigidbody.h"
#include "PhysicsManager.h"

#include <math.h>

namespace S2DE {

	void Rigidbody::FixedUpdate(float delta) {
		vec2f vel = m_velocity * delta;

		vec2f slide = Move(vel);
		Move(slide);
	}


	vec2f Rigidbody::Move(const vec2f& vel) {
		vec2f position = GetObject()->GetWorldPosition();
		vec2f target = position + vel;
		vec2f size = GetSize();
		vec2f offset = GetOffset();

		box2f A = GetWorldBounds();
		box2f C = {
			{ target.x + offset.x, target.y + offset.y },
			{ target.x + offset.x + size.x, target.y + offset.y + size.y }
		};

		std::list<std::shared_ptr<Collider>> intersections = PhysicsManager::GetIntersectingColliders(C);

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = intersections.begin(); it != intersections.end(); it++) {
			if ((*it).get() != this && !(*it).get()->IsTrigger()) {
				box2f B = (*it)->GetWorldBounds();
				return Resolve(A, B, vel, position);
			}
		}

		GetObject()->SetWorldPosition(position + vel);
		return {0,0};
	}


	vec2f Rigidbody::Resolve(const box2f& A, const box2f& B, const vec2f& v, vec2f& p) {
		vec2f d;
		vec2f t;

		vec2f move;
		vec2f slide;

		if (A.min.x < B.min.x) {
			d.x = B.min.x - A.max.x;
		} else {
			d.x = A.min.x - B.max.x;
		}

		if (A.min.y < B.min.y) {
			d.y = B.min.y - A.max.y;
		} else {
			d.y = A.min.y - B.max.y;
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
			if (t.x < t.y) slide.y = v.y - move.y;
			if (t.y < t.x) slide.x = v.x - move.x;
		}

		GetObject()->SetWorldPosition(p + move);

		return slide;
	}


	void Rigidbody::SetVelocity(vec2f velocity) { m_velocity = velocity; }
	vec2f Rigidbody::GetVelocity() { return m_velocity; }

}