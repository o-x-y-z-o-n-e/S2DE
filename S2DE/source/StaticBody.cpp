#include "StaticBody.h"

using namespace S2DE;

void StaticBody::SetBounds(rect bounds) {
	this->bounds = bounds;
}

rect StaticBody::GetBounds() {
	return bounds;
}