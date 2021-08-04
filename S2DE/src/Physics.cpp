#include "Physics.h"

using namespace S2DE;

bool Physics::RectIntersects(rect& rect1, vect& rect1offset, rect& rect2, vect& rect2offset) {
	if ((rect1offset.x) + (rect1.x + rect1.w) > (rect2offset.x) + (rect2.x)            &&
		(rect1offset.x) + (rect1.x)	          < (rect2offset.x) + (rect2.x + rect2.w)) return true;

	if ((rect1offset.y) + (rect1.y + rect1.h) > (rect2offset.y) + (rect2.y)            &&
		(rect1offset.y) + (rect1.y)	          < (rect2offset.y) + (rect2.y + rect2.h)) return true;

	return false;
}