#include "Global.h"
#include "LayerManager.h"

namespace S2DE {

	Chain LayerManager::s_layers;

	bool LayerManager::AttachLayer(Layer* layer) {
		int level = layer->GetLevel();

		Chain::Iterator it = s_layers.Begin();
		Layer* current = (Layer*)it.Next();
		int index = 0;

		while (true) {
			if (current == nullptr) {
				//reached the end.
				s_layers.Append(layer);
				return;
			}

			int clvl = current->GetLevel();
			if (clvl == level) {
				LogCoreError("Could not add layer (%d). A layer already exists with that Level!", layer->GetLevel());
				return;
			} else if (level > clvl) {
				//insert
				s_layers.Insert(index + 1, layer);
				return;
			}

			current = (Layer*)it.Next();
			index++;
		}
	}

}