#pragma once

#include "S2DE.h"

class Circle : public S2DE::Component {

public:
	void DynamicUpdate(float delta);
	void FixedUpdate(float delta);

private:
	float m_counter;
	bool m_go;

};