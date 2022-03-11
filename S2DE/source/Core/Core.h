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
		
		static bool s_hasInit;
		static bool s_isRunning;
		static int s_tickCounter;

		static float s_fixedDeltaCounter;

		static float s_renderTimeStep;
		static float s_renderTickCounter;

	};


}

#endif