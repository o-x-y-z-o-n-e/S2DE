#include "PhysicsManager.h"

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



	std::list<std::shared_ptr<Collider>> PhysicsManager::GetIntersectingColliders(rec2f area) {
		std::list<std::shared_ptr<Collider>> intersects;

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = s_colliders.begin(); it != s_colliders.end(); it++) {
			if ((*it)->Intersects(area))
				intersects.push_back(*it);
		}

		return intersects;
	}


	std::list<vec2i> PhysicsManager::GetIntersectionSectors(std::shared_ptr<Collider> collider) {
		std::list<vec2i> sectors;

		rec2f bounds = collider->GetWorldBounds();
		rec2i sec;

		sec.x = bounds.x / SECTOR_SIZE;
		sec.y = bounds.y / SECTOR_SIZE;
		sec.w = bounds.w / SECTOR_SIZE;
		sec.h = bounds.h / SECTOR_SIZE;

		if (bounds.x < 0) sec.x--;
		if (bounds.y < 0) sec.y--;
		if (bounds.w > 0) sec.w++;
		if (bounds.h > 0) sec.h++;

		for (int x = sec.x; x < sec.w; x++)
			for (int y = sec.y; y < sec.h; y++)
				sectors.push_back({ x, y });

		return sectors;
	}


	void PhysicsManager::Step(float delta) {
		// velocity
		

		// collisions
		std::list<std::shared_ptr<Collider>>::iterator it_i = s_colliders.begin();
		std::list<std::shared_ptr<Collider>>::iterator it_j;
		for(int i = 0; i < s_colliders.size() - 1; i++) {
			std::shared_ptr<Collider> c1 = *it_i;
			it_i++;
			it_j = it_i;
			for(int j = i + 1; j < s_colliders.size(); j++) {
				std::shared_ptr<Collider> c2 = *it_j;
				
				// CHECK COLLISION HERE
				if(c1->Intersects(c2)) {

				}

				it_j++;
			}
		}


	}


}