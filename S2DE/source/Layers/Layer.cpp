#include "Layer.h"

namespace S2DE {

	Layer::Layer(int level) {
		m_level = level;
	}

	int Layer::GetLevel() { return m_level; }

	void Layer::Update() {}

	Layer::~Layer() {}

}