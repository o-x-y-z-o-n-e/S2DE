#ifndef S2DE_APPLICATION_H
#define S2DE_APPLICATION_H

#define S2DE_WINDOWED 0
#define S2DE_FULLSCREEN 1
#define S2DE_BORDERLESS 2

namespace S2DE {

	int Init();
	void Start();
	void Close();
	bool IsRunning();

	void Log(const char* format, ...);
	void LogWarning(const char* format, ...);
	void LogError(const char* format, ...);

	void SetWindowMode(int mode);
	void SetTitle(const char* title);
	void SetTargetFrameRate(int fps);

}

#endif