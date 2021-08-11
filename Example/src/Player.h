#pragma once

#include <S2DE.h>

class Player : public S2DE::Component {

public:
	//Player();
	void Init();
	void FixedUpdate(float delta);

private:
	S2DE::Sprite* sprite;

	float counter;
	void Move(float delta);
	S2DE::vect velocity;
	S2DE::rect bounds;

	S2DE::rect floor;
};
