#include "Collider.h"
#include "PhysicsManager.h"
#include "Global.h"

#include <stdio.h>

namespace S2DE {


	void Collider::Init() {
		PhysicsManager::Attach(PTR_THIS(Collider));
	}


	Collider::~Collider() {
		PhysicsManager::Dettach(PTR_THIS(Collider));
	}


	void Collider::SetSize(vec2f size) { m_size = size; }
	void Collider::SetOffset(vec2f offset) { m_offset = offset; }
	vec2f Collider::GetSize() { return m_size; }
	vec2f Collider::GetOffset() { return m_offset; }
	void Collider::SetTrigger(bool trigger) { m_isTrigger = trigger; }
	bool Collider::IsTrigger() { return m_isTrigger; }


	box2f Collider::GetLocalBounds() {
		return {
			{ m_offset.x, m_offset.y },
			{ m_offset.x + m_size.x, m_offset.y + m_size.y }
		};
	}

	box2f Collider::GetWorldBounds() {
		vec2f p = GetObject()->GetWorldPosition();
		return {
			{ p.x + m_offset.x, p.y + m_offset.y },
			{ p.x + m_offset.x + m_size.x, p.y + m_offset.y + m_size.y }
		};
	}



	bool Collider::Intersects(std::shared_ptr<Collider> other) {
		return Intersects(other->GetWorldBounds());
	}


	bool Collider::Intersects(const box2f& area) {
		box2f A = GetWorldBounds();
		bool h = A.min.x < area.max.x && A.max.x > area.min.x;
		bool v = A.min.y < area.max.y && A.max.y > area.min.y;
		return h && v;
	}


	bool Collider::Intersects(const ray2f& ray, float* distance) {
		box2f A = GetWorldBounds();

		float t_min_x = (A.min.x - ray.origin.x) / ray.direction.x;
		float t_max_x = (A.max.x - ray.origin.x) / ray.direction.x;

		float t_min_y = (A.min.y - ray.origin.y) / ray.direction.y;
		float t_max_y = (A.max.y - ray.origin.y) / ray.direction.y;

		float t_min = fmaxf(fminf(t_min_x, t_max_x), fminf(t_min_y, t_max_y));
		float t_max = fminf(fmaxf(t_min_x, t_max_x), fmaxf(t_min_y, t_max_y));

		// If ray intersects but AABB is 'behind' the ray origin.
		if (t_max < 0)
			return false;

		// No intersection.
		if (t_max < t_min)
			return false;

		float t = fminf(t_min, t_max);

		// If the first intersection is further than ray distance.
		if (t > ray.distance)
			return false;

		// Else, there was an intersection.
		*distance = t;
		return true;
	}

}