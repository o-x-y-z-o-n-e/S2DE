#define SDL_MAIN_HANDLED

#include "S2DE.h"

int main(int argc, char** args) {
	if(!S2DE::Init()) return 1;

	S2DE::Start();

	return 0;
}