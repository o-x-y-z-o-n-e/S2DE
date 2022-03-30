#include "Player.h"

#define m_mass 1.0f
#define m_walk 20.0f
#define m_friction 0.25f
#define m_jump 80.0f
#define m_gravity 160.0f

void Player::DynamicUpdate(float delta) {
	if (m_isGrounded && S2DE::Input::IsPressed(S2DE_KEY_SPACE)) {
		m_targetVelocity.y = m_jump / m_mass;
	}
}

void Player::FixedUpdate(float delta) {
    float moveInput = 0;

    if(S2DE::Input::IsHeld(S2DE_KEY_A))
        moveInput -= 1;
    if(S2DE::Input::IsHeld(S2DE_KEY_D))
        moveInput += 1;

    m_targetVelocity.x += (moveInput * m_walk) / m_mass;
    m_targetVelocity.x -= (m_targetVelocity.x) * m_friction;

    SetVelocity(m_targetVelocity);

	S2DE::Rigidbody::FixedUpdate(delta);

	S2DE::ray2f ray;
	ray.origin = GetObject()->GetLocalPosition();
	ray.origin.x -= 9;
	ray.origin.y -= 7;
	ray.direction = { 0, -1 };
	ray.distance = 1;

	S2DE::hitinfo hit = S2DE::Physics::Raycast(ray);
	m_isGrounded = hit.hit;

	if (!m_isGrounded) {
		m_targetVelocity.y -= m_gravity * delta;
		if (m_targetVelocity.y < -120.0f)
			m_targetVelocity.y = -120.0f;
	} else {
		m_targetVelocity.y = 0;
	}
}