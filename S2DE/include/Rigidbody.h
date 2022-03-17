#ifndef S2DE_RIGIDBODY_H
#define S2DE_RIGIDBODY_H

#include "Collider.h"

namespace S2DE {

	class Rigidbody : public Collider {

	public:
		void FixedUpdate(float delta);

		void SetVelocity(vec2f velocity);
		vec2f GetVelocity();

	private:
		vec2f m_velocity;

	};

}

#endif