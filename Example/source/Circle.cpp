#include "Circle.h"
#include <math.h>

void Circle::DynamicUpdate(float delta) {
	if (S2DE::Input::IsPressed(S2DE_KEY_SPACE)) {
		m_go = !m_go;
	}
}

void Circle::FixedUpdate(float delta) {
	if (!m_go)
		return;

	m_counter += delta;

	S2DE::vec2f pos = GetObject()->GetLocalPosition();

	pos.x = cosf(m_counter) * 32;
	pos.y = sinf(m_counter) * 32;

	GetObject()->SetLocalPosition(pos);
}