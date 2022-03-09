#include "Circle.h"
#include <math.h>

void Circle::FixedUpdate(float delta) {
	m_counter += delta;

	S2DE::vec2f pos = GetObject()->GetLocalPosition();

	pos.x = cosf(m_counter) * 32;
	pos.y = sinf(m_counter) * 32;

	GetObject()->SetLocalPosition(pos);
}