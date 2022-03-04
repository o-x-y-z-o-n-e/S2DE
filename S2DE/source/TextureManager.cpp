#include "TextureManager.h"
#include "Global.h"
#include "Window.h"
#include "Util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_set>

namespace S2DE {


	void* TextureManager::m_textureTable[TEXTURE_TABLE_SIZE];
	int TextureManager::m_textureTableCount;


	void TextureManager::Init() {

	}


	//-------------------------------------------------------------------------------------------------


	int TextureManager::GetEmptyIndex(std::string key) {
		size_t hash = std::hash<std::string>{}(key);
		int start = hash % TEXTURE_TABLE_SIZE;
		int index = start;

		int i = 0;
		while (m_textureTable[index] != NULL) {
			index = start + (i * i);
		}

		return index;
	}


	//-------------------------------------------------------------------------------------------------


	int TextureManager::LoadTextureData(std::string path) {
		if (m_textureTableCount >= TEXTURE_TABLE_SIZE) {
			LogCoreError("Run out of texture table memory!");
			LogCoreError("Could not load file '%s'", path);
			return -1;
		}

		int index = GetEmptyIndex(path);

		int wantedFormat = STBI_rgb_alpha;
		int width, height, originFormat;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &originFormat, wantedFormat);
		if (data == NULL) {
			LogCoreError("Could not load file '%s'", path);
			return -1;
		}

		int depth, pitch;
		uint32_t pixelFormat;
		if (wantedFormat == STBI_rgb) {
			depth = 24;
			pitch = 3 * width;
			pixelFormat = SDL_PIXELFORMAT_RGB24;
		} else {
			depth = 32;
			pitch = 4 * width;
			pixelFormat = SDL_PIXELFORMAT_RGBA32;
		}

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, width, height, depth, pitch, pixelFormat);

		if (surface == NULL) {
			stbi_image_free(data);
			LogCoreError("Could not load file '%s'", path);
			return -1;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);

		SDL_FreeSurface(surface);
		stbi_image_free(data);

		if (texture == NULL) {
			LogCoreError("Could not load file '%s'", path);
			return -1;
		}

		m_textureTable[index] = texture;
		m_textureTableCount++;
		return index;
	}


	//-------------------------------------------------------------------------------------------------


	int TextureManager::CreateTextureData(std::string name, int w, int h) {
		if (m_textureTableCount >= TEXTURE_TABLE_SIZE) {
			LogCoreError("Run out of texture table memory!");
			LogCoreError("Could create texture '%s'", name);
			return -1;
		}

		int index = GetEmptyIndex(name);

		SDL_Texture* texture = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);

		if (texture == NULL) {
			LogCoreError("Could create texture '%s'", name);
			return -1;
		}

		m_textureTable[index] = texture;
		m_textureTableCount++;
		return index;
	}


	//-------------------------------------------------------------------------------------------------


	void TextureManager::FreeTextureData(int id) {
		if (m_textureTable[id] == NULL)
			return;

		SDL_DestroyTexture((SDL_Texture*)m_textureTable[id]);
		m_textureTable[id] = NULL;
		m_textureTableCount--;
	}


	//-------------------------------------------------------------------------------------------------


	void* TextureManager::GetTextureData(int id) {
		if (id < 0)
			return NULL;

		return m_textureTable[id];
	}


	//-------------------------------------------------------------------------------------------------


	int TextureManager::QueryTextureData(int id, int* access, int* w, int* h) {
		if (id < 0)
			return 0;

		if (SDL_QueryTexture((SDL_Texture*)m_textureTable[id], NULL, access, w, h))
			return 1;
		else return 0;
	}


	/*  My attempt at loading .bmp files. It worked, although the textures came out upside down. And I couldn't fix it :(
	SDL_Texture* LoadBMP(const char* path) {
		std::ifstream file;
		file.open(path, std::ios::binary);
		if (!file.is_open())
			return NULL;

		uint8_t header[18];
		file.read((char*)header, 18);

		if (header[0] != 0x42 || header[1] != 0x4D)
			goto fail2;

		uint32_t fileSize = BytesToUInt32(&header[2]);
		uint32_t dataOffset = BytesToUInt32(&header[10]);
		uint32_t dibSize = BytesToUInt32(&header[14]);

		int dibMode = 0;
		switch (dibSize) {
		case 40:
			dibMode = 1;
			break;
		case 52:
			dibMode = 2;
			break;
		case 56:
			dibMode = 3;
			break;
		case 108:
			dibMode = 4;
			break;
		case 124:
			dibMode = 5;
			break;
		default:
			printf("[S2DE] ERROR: Could not load '%s' DIB Header size %d is not supported.\n", path, dibSize);
			goto fail2;
		}

		const int dibOffset = 18;
		uint8_t* dib = (uint8_t*)malloc(sizeof(uint8_t) * (dibSize - 4));
		if (dib == NULL) goto fail2;

		file.read((char*)dib, dibSize - 4);

		uint32_t width = abs(BytesToInt32(&dib[18 - dibOffset]));
		uint32_t height = abs(BytesToInt32(&dib[22 - dibOffset]));
		uint16_t planes = BytesToUInt16(&dib[26 - dibOffset]);
		uint16_t colorDepth = BytesToUInt16(&dib[28 - dibOffset]);
		uint32_t compression = BytesToUInt32(&dib[30 - dibOffset]);
		uint32_t rawSize = BytesToUInt32(&dib[34 - dibOffset]);
		int32_t hres = BytesToInt32(&dib[38 - dibOffset]);
		int32_t vres = BytesToInt32(&dib[42 - dibOffset]);
		uint32_t colors = BytesToUInt32(&dib[46 - dibOffset]);

		if (compression != 0) {
			printf("[S2DE] ERROR: Could not load '%s' compression mode %d is not supported.\n", path, compression);
			goto fail1;
		}

		if (colorDepth != 32 && colorDepth != 24) {
			printf("[S2DE] ERROR: Could not load '%s' %dbit color depth is not supported.\n", path, colorDepth);
			goto fail1;
		}

		//SDL_Texture* texture = SDL_CreateTexture(Window::GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, width, height);


		int pitch = ((colorDepth * width) / 32) * 4;
		uint32_t format;

		if (colorDepth == 24) {
			//pitch = width * 3;
			format = SDL_PIXELFORMAT_RGB24;
		} else if (colorDepth == 32) {
			//pitch = width * 4;
			format = SDL_PIXELFORMAT_RGBA32;
		}

		uint8_t* pixels = (uint8_t*)malloc(sizeof(uint8_t) * pitch * height);
		if (pixels == NULL) goto fail2;


		uint8_t sample[3];
		for (int h = 0; h < height; h++) {
			int rowOffset = pitch * h;
			file.seekg(dataOffset + rowOffset, std::ios::beg);

			for (int w = 0; w < width; w++) {
				if (colorDepth == 24) {
					file.read((char*)sample, 3);

					pixels[(h * pitch) + w] = sample[0];
					pixels[(h * pitch) + w+1] = sample[1];
					pixels[(h * pitch) + w+2] = sample[2];

				} else if (colorDepth == 32) {
					//file.read((char*)sample, 4);

					//pixels[(h * pitch) + w] = sample[3];
					//pixels[(h * pitch) + w + 1] = sample[2];
					//pixels[(h * pitch) + w + 2] = sample[1];
					//pixels[(h * pitch) + w + 2] = sample[0];
				}
			}
		}

		//file.seekg(dataOffset, std::ios::beg);
		//file.read((char*)pixels, pitch * height);

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, colorDepth, pitch, format);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);


		free(dib);
		free(pixels);
		SDL_FreeSurface(surface);

		file.close();
		return texture;


	fail2:
		free(dib);
	fail1:
		file.close();
		return NULL;
	}

	*/

}