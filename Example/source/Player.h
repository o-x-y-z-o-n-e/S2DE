#pragma once

#include "S2DE.h"

class Player : public S2DE::Rigidbody {

public:
	void DynamicUpdate(float delta);
    void FixedUpdate(float delta);

private:
    S2DE::vec2f m_targetVelocity;

};