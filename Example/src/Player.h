#pragma once

#include <S2DE.h>

using namespace S2DE;

class Player : public Component {

public:
	void FixedUpdate(float delta);

private:
	float counter;
	void Move(float delta);
	Vector velocity;
};
