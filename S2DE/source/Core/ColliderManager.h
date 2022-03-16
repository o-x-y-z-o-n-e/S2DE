#ifndef S2DE_COLLIDER_MANAGER_H
#define S2DE_COLLIDER_MANAGER_H

#include "Collider.h"

#include <memory>

namespace S2DE {

	class ColliderManager {

	public:
		static void Attach(std::shared_ptr<Collider> collider);
		static void Dettach(std::shared_ptr<Collider> collider);

		static std::list<std::shared_ptr<Collider>> GetIntersectingColliders(std::shared_ptr<Collider> collider);

	private:
		static std::list<std::shared_ptr<Collider>> s_colliders;

	};

}

#endif