#ifndef S2DE_CAMERA_H
#define S2DE_CAMERA_H

#include "Types.h"

namespace S2DE::Camera {

	void SetPosition(float x, float y);
	//void SetPosition(int x, int y);
	void SetPosition(vec2f position);
	//void SetPosition(vec2i position);

	void GetPosition(float* x, float* y);
	//void GetPosition(int* x, int* y);
	vec2f GetPosition();
	//void GetPosition(vec2i* position);

}

#endif