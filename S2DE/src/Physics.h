#pragma once

#include "Core.h"

namespace S2DE {

	class Physics {

	public:
		static bool RectIntersects(rect& rect1, vect& rect1offset, rect& rect2, vect& rect2offset);

	};

}