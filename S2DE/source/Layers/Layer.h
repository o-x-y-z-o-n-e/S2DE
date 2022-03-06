#ifndef S2DE_LAYER_H
#define S2DE_LAYER_H

namespace S2DE {

	class Layer {

	public:
		Layer(int level);
		virtual ~Layer();
		virtual void Update();
		//virtual void ProcessEvents();
		int GetLevel();

	private:
		int m_level;
	};

}

#endif