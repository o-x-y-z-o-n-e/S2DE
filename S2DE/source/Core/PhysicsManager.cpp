#include "Physics.h"
#include "PhysicsManager.h"

#include <stdarg.h>

#define SECTOR_SIZE 64

namespace S2DE {

	std::list<std::shared_ptr<Collider>> PhysicsManager::s_colliders;

	void PhysicsManager::Attach(std::shared_ptr<Collider> collider) {
		s_colliders.push_back(collider);
	}

	void PhysicsManager::Dettach(std::shared_ptr<Collider> collider) {
		s_colliders.remove(collider);
	}


	std::list<std::shared_ptr<Collider>> PhysicsManager::GetIntersectingColliders(std::shared_ptr<Collider> collider) {
		std::list<std::shared_ptr<Collider>> intersects;

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = s_colliders.begin(); it != s_colliders.end(); it++) {
			if (*it != collider)
				if (collider->Intersects(*it))
					intersects.push_back(*it);
		}

		return intersects;
	}



	std::list<std::shared_ptr<Collider>> PhysicsManager::GetIntersectingColliders(box2f area) {
		std::list<std::shared_ptr<Collider>> intersects;

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = s_colliders.begin(); it != s_colliders.end(); it++) {
			if ((*it)->Intersects(area))
				intersects.push_back(*it);
		}

		return intersects;
	}


	std::list<hitinfo> PhysicsManager::GetIntersectingColliders(ray2f ray) {
		std::list<hitinfo> intersects;

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = s_colliders.begin(); it != s_colliders.end(); it++) {
			float t = 0;
			if ((*it)->Intersects(ray, &t)) {
				hitinfo hit;

				hit.distance = t;
				hit.point = ray.origin + (ray.direction * t);
				hit.collider = *it;
				hit.hit = true;

				intersects.push_back(hit);
			}
		}

		return intersects;
	}


	hitinfo PhysicsManager::GetClosetIntersectingCollider(ray2f ray) {
		hitinfo hit;
		hit.hit = false;
		hit.distance = 1000.0F;

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = s_colliders.begin(); it != s_colliders.end(); it++) {
			float t = 0;
			if ((*it)->Intersects(ray, &t)) {
				if (hit.distance == 0 || t < hit.distance) {
					hit.distance = t;
					hit.point = ray.origin + (ray.direction * t);
					hit.collider = *it;
					hit.hit = true;
				}
			}
		}

		return hit;
	}


	std::list<vec2i> PhysicsManager::GetIntersectionSectors(std::shared_ptr<Collider> collider) {
		std::list<vec2i> sectors;

		box2f bounds = collider->GetWorldBounds();
		box2i sec;

		sec.min.x = bounds.min.x / SECTOR_SIZE;
		sec.min.y = bounds.min.y / SECTOR_SIZE;
		sec.max.x = bounds.max.x / SECTOR_SIZE;
		sec.max.y = bounds.max.y / SECTOR_SIZE;

		if (bounds.min.x < 0) sec.min.x--;
		if (bounds.min.y < 0) sec.min.y--;
		if (bounds.max.x > 0) sec.max.x++;
		if (bounds.max.y > 0) sec.max.y++;

		for (int x = sec.min.x; x < sec.max.x; x++)
			for (int y = sec.min.y; y < sec.max.y; y++)
				sectors.push_back({ x, y });

		return sectors;
	}


	mask mask::GetMask(int n, ...) {
		mask m;
		va_list valist;

		va_start(valist, n);

		for(int i = 0; i < n; i++) {
			int b = va_arg(valist, int);
			if(b >= 0 && b < 32)
				m.bitmask |= 0x0001 << b;
		}
		va_end(valist);

		return m;
	}

	hitinfo Physics::Raycast(const ray2f& ray) {
		return Raycast(ray, mask::all(), false);
	}

	hitinfo Physics::Raycast(const ray2f& ray, const mask& layers) {
		return Raycast(ray, layers, false);
	}

	hitinfo Physics::Raycast(const ray2f& ray, const mask& layers, bool ignoreTrigger) {
		// USEE LAYER & IGNORE TRIGGER INFO
		return PhysicsManager::GetClosetIntersectingCollider(ray);
	}


}