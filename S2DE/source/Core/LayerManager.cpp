#include "Global.h"
#include "LayerManager.h"

namespace S2DE {

	Chain<Layer*> LayerManager::s_layers;

	bool LayerManager::AttachLayer(Layer* layer) {
		int level = layer->GetLevel();

		Chain<Layer*>::Iterator it = s_layers.Begin();
		Layer* current = it.Next();
		int index = 0;

		while (true) {
			if (current == nullptr) {
				//reached the end.
				s_layers.Append(layer);
				return true;
			}

			int clvl = current->GetLevel();
			if (clvl == level) {
				LogCoreError("Could not add layer (%d). A layer already exists with that Level!", layer->GetLevel());
				return false;
			} else if (level > clvl) {
				//insert
				s_layers.Insert(index + 1, layer);
				return true;
			}

			current = it.Next();
			index++;
		}

		return false;
	}

	Layer* LayerManager::GetLayer(int layer) {
		Chain<Layer*>::Iterator it = s_layers.Begin();
		Layer* current = it.Next();
		int index = 0;

		while (current != nullptr) {
			if (layer == current->GetLevel())
				return current;

			current = it.Next();
			index++;
		}

		return nullptr;
	}


	void LayerManager::Process() {
		Chain<Layer*>::Iterator it = s_layers.Begin();
		Layer* current;

		while((current = it.Next()) != nullptr) {
			current->Update();
		}

		while((current = it.Next()) != nullptr) {
			current->ProcessEvents();
		}
	}


}