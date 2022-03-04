#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>

#define TEXTURE_TABLE_SIZE 1000

namespace S2DE {

	class TextureManager {

	public:
		static void Init();
		static int LoadTextureData(std::string path);
		static int CreateTextureData(std::string name, int w, int h);
		static void FreeTextureData(int id);
		static void* GetTextureData(int id);
		static int QueryTextureData(int id, int* access, int* w, int* h);

	private:
		static void* m_textureTable[TEXTURE_TABLE_SIZE];
		static int m_textureTableCount;
		static int GetEmptyIndex(std::string key);

	};
}

#endif