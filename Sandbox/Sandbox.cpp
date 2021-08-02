#define SDL_MAIN_HANDLED
#include <iostream>
#include "Sandbox.h"

int main() {
    std::cout << "Hello World!\n";

	S2DE::Core::Init();
	S2DE::Core::Start();
}