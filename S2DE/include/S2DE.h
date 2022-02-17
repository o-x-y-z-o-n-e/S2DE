#ifndef S2DE_H
#define S2DE_H

//this is where applications can integrate S2DE with

namespace S2DE {

	int Init();
	void Start();
	void Close();
	bool IsRunning();
	void Loop();

}

#include "Component.h"
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include "Types.h"

#endif