#pragma once

#include <S2DE.h>

class Player : public S2DE::Component {

public:
	void FixedUpdate(float delta);

private:
	float counter;
	void Move(float delta);
	S2DE::vect velocity;
	S2DE::rect bounds;

	S2DE::rect floor;
};
