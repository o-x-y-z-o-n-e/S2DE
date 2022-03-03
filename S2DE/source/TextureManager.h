#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>

#define TEXTURE_TABLE_SIZE 1000

namespace S2DE {

	class TextureManager {

	public:
		static void Init();
		static int LoadTextureData(std::string path);
		static void FreeTextureData(int id);
		static void* GetTextureData(int id);

	private:
		static void* m_textureTable[TEXTURE_TABLE_SIZE];
		static int m_textureTableCount;

	};
}

#endif