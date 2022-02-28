#ifndef S2DE_TEXTURE_H
#define S2DE_TEXTURE_H

#include <string>

namespace S2DE {

    class Texture {
	public:
		Texture();
		~Texture();
		bool Load(std::string path);
		int GetID();
		int GetWidth();
		int GetHeight();

	private:
		int m_id;
		int m_width;
		int m_height;
	};

}

#endif