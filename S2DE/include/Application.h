#ifndef S2DE_APPLICATION_H
#define S2DE_APPLICATION_H

namespace S2DE {

	int Init();
	void Start();
	void Close();
	bool IsRunning();

	void Log(const char* format, ...);
	void LogWarning(const char* format, ...);
	void LogError(const char* format, ...);

}

#endif