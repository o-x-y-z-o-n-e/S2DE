#ifndef S2DE_COLLIDER_MANAGER_H
#define S2DE_COLLIDER_MANAGER_H

#include "Collider.h"

#include <memory>

namespace S2DE {

	class PhysicsManager {

	public:
		static void Attach(std::shared_ptr<Collider> collider);
		static void Dettach(std::shared_ptr<Collider> collider);

		static std::list<std::shared_ptr<Collider>> GetIntersectingColliders(std::shared_ptr<Collider> collider);
		static std::list<std::shared_ptr<Collider>> GetIntersectingColliders(rec2f area);

		static std::list<vec2i> GetIntersectionSectors(std::shared_ptr<Collider> collider);

		static void Step(float delta);

	private:
		static std::list<std::shared_ptr<Collider>> s_colliders;

	};

}

#endif