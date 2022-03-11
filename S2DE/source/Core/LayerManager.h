#ifndef S2DE_LAYER_MANAGER_H
#define S2DE_LAYER_MANAGER_H

#include "Types.h"
#include "Layers/Layer.h"

//#include <vector>
#include <list>

namespace S2DE {

	class LayerManager {

	public:
		static Layer* GetLayer(int index);
		static bool AttachLayer(Layer* layer);
		static bool Exists(int index);
		static void Process();

	private:
		static std::list<Layer*> s_layers;
	};

}

#endif