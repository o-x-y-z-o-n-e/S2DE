#ifndef S2DE_LAYER_H
#define S2DE_LAYER_H

namespace S2DE {

	class Layer {

	public:
		virtual ~Layer();
		virtual void Update();
		//virtual void ProcessEvents();

	};

}

#endif