#include "ColliderManager.h"

namespace S2DE {

	std::list<std::shared_ptr<Collider>> ColliderManager::s_colliders;

	void ColliderManager::Attach(std::shared_ptr<Collider> collider) {
		s_colliders.push_back(collider);
	}

	void ColliderManager::Dettach(std::shared_ptr<Collider> collider) {
		s_colliders.remove(collider);
	}


	std::list<std::shared_ptr<Collider>> ColliderManager::GetIntersectingColliders(std::shared_ptr<Collider> collider) {
		std::list<std::shared_ptr<Collider>> intersects;

		std::list<std::shared_ptr<Collider>>::iterator it;
		for (it = s_colliders.begin(); it != s_colliders.end(); it++) {
			if (*it != collider)
				if (collider->Intersects(*it))
					intersects.push_back(*it);
		}

		return intersects;
	}

}