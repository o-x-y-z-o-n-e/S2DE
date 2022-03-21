#include "Player.h"

#define m_mass 1.0f
#define m_walk 10.0f
#define m_friction 0.25f
#define m_jump 40.0f
#define m_gravity 40.0f

void Player::FixedUpdate(float delta) {
    S2DE::Rigidbody::FixedUpdate(delta);

    float moveInput = 0;

    if(S2DE::Input::IsHeld(S2DE_KEY_A))
        moveInput -= 1;
    if(S2DE::Input::IsHeld(S2DE_KEY_D))
        moveInput += 1;

    m_targetVelocity.x += (moveInput * m_walk) / m_mass;
    m_targetVelocity.x -= (m_targetVelocity.x) * m_friction;

    if(S2DE::Input::IsPressed(S2DE_KEY_SPACE)) {
        m_targetVelocity.y = m_jump / m_mass;
    }

    m_targetVelocity.y -= m_gravity * delta;
    if(m_targetVelocity.y < -64.0f)
        m_targetVelocity.y = -64.0f;

    SetVelocity(m_targetVelocity);
}