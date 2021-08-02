#pragma once

#include "../S2DE.h"

using namespace S2DE;

class Player : public Component {

public:
	void Update(float delta);

private:
	float counter;
};
