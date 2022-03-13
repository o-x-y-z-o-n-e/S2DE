#ifndef S2DE_TEXTURE_H
#define S2DE_TEXTURE_H

#include <string>
#include <memory>

namespace S2DE {

    class Texture {
	public:
		Texture();
		static std::shared_ptr<Texture> Load(std::string path);
		static std::shared_ptr<Texture> Create(std::string name, int w, int h);
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