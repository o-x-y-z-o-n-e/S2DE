#ifndef S2DE_CONSOLE_H
#define S2DE_CONSOLE_H

namespace S2DE {

	class Console {

	public:
		static void Init();

	private:
		static bool m_hasInit;

	};


	void LogCore(const char* message);
	void LogCoreWarning(const char* message);
	void LogCoreError(const char* message);

}

#endif