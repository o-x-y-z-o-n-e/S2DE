#ifndef S2DE_CORE_H
#define S2DE_CORE_H

namespace S2DE {

	class Core {
		
	public:
		static int Init();
		static void Start();
		static void Close();
		static bool IsRunning();
		static void SetTargetFrameRate(int fps);

	private:
		static void Loop();
		
		static bool m_hasInit;
		static bool m_isRunning;
		static int m_tickCounter;

		static float m_fixedDeltaCounter;

		static float m_renderTimeStep;
		static float m_renderTickCounter;

	};


}

#endif