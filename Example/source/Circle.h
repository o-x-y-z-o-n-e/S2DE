#pragma once

#include "S2DE.h"

class Circle : public S2DE::Component {

public:
	void FixedUpdate(float delta);

private:
	float m_counter;

};