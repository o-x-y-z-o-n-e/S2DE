#ifndef S2DE_LAYER_MANAGER_H
#define S2DE_LAYER_MANAGER_H

#include "Types.h"
#include "Layers/Layer.h"

//#include <vector>

namespace S2DE {

	class LayerManager {

	public:
		static bool AttachLayer(Layer* layer);

	private:
		static Chain s_layers;
	};

}

#endif