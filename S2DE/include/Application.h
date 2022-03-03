#ifndef S2DE_APPLICATION_H
#define S2DE_APPLICATION_H

namespace S2DE {

	int Init();
	void Start();
	void Close();
	bool IsRunning();

	void Log(const char* message);
	void LogWarning(const char* message);
	void LogError(const char* message);

}

#endif