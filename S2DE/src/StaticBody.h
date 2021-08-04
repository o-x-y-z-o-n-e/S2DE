#pragma once

#include "Core.h"
#include "Physics.h"
#include "Component.h"

namespace S2DE {

	class StaticBody : S2DE::Component {
		S2DE::rect GetBounds();
		void SetBounds(S2DE::rect bounds);

	private:
		S2DE::rect bounds;

	};

}