#ifndef S2DE_TEXTURE_H
#define S2DE_TEXTURE_H

#include <SDL.h>
#include <string>

namespace S2DE {

    class Texture {
	public:
		Texture();
		~Texture();
		bool Load(std::string path);
		void Free();
		int GetWidth();
		int GetHeight();
		SDL_Texture* GetSDL();

	private:
		SDL_Texture* m_tex;
		int m_width;
		int m_height;
	};

}

#endif