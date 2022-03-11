#include "Global.h"
#include "LayerManager.h"

namespace S2DE {

	std::list<Layer*> LayerManager::s_layers;

	bool LayerManager::AttachLayer(Layer* layer) {
		int level = layer->GetLevel();


		std::list<Layer*>::iterator it;
		for (it = s_layers.begin(); it != s_layers.end(); it++) {
			int clvl = (*it)->GetLevel();

			if (clvl == level) {
				LogCoreError("Could not add layer (%d). A layer already exists with that Level!", layer->GetLevel());
				return false;
			} else if (level > clvl) {
				//insert
				//s_layers.Insert(index + 1, layer);
				s_layers.insert(it, layer);
				return true;
			}
		}

		// reached end
		s_layers.push_back(layer);
		return true;
	}


	Layer* LayerManager::GetLayer(int layer) {
		std::list<Layer*>::iterator it;
		for (it = s_layers.begin(); it != s_layers.end(); it++) {
			if (layer == (*it)->GetLevel())
				return (*it);
		}

		return nullptr;
	}


	void LayerManager::Process() {
		std::list<Layer*>::iterator it;
		for (it = s_layers.begin(); it != s_layers.end(); it++) {
			(*it)->Update();
		}

		//process events
	}


}