#include "TextureManager.h"
#include "Window.h"
#include "Util.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

namespace S2DE {

	namespace TextureManager {

		SDL_Texture* texture_table[TEXTURE_TABLE_SIZE];
		int texture_table_count = 0;


		void InitTextureManager() {

		}


		//-------------------------------------------------------------------------------------------------


		int LoadTextureData(const char* path) {
			if (texture_table_count >= TEXTURE_TABLE_SIZE)
				return -1;

			int hash = GetStringHash(path);
			int start = hash % TEXTURE_TABLE_SIZE;
			int index = start;

			int i = 0;
			while (texture_table[index] != NULL) {
				index = start + (i * i);
			}

			
			SDL_Surface* surface = IMG_Load(path);
			if(surface == NULL)
				return 0;
			texture_table[index] = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);
			texture_table_count++;
			SDL_FreeSurface(surface);
			

			//texture_table[index] = LoadBMP(path);
			if (texture_table[index] == NULL)
				return -1;

			texture_table_count++;
			return index;
		}


		//-------------------------------------------------------------------------------------------------


		void FreeTextureData(int id) {
			if (texture_table[id] == NULL)
				return;

			SDL_DestroyTexture(texture_table[id]);
			texture_table[id] = NULL;
			texture_table_count--;
		}


		//-------------------------------------------------------------------------------------------------


		SDL_Texture* GetTextureData(int id) {
			if (id < 0)
				return NULL;

			return texture_table[id];
		}


		//-------------------------------------------------------------------------------------------------


		SDL_Texture* LoadBMP(const char* path) {
			std::ifstream file;
			file.open(path, std::ios::binary);
			if (!file.is_open())
				return NULL;

			u_int8_t header[18];
			file.read((char*)header, 18);

			if (header[0] != 0x42 || header[1] != 0x4D)
				goto fail2;

			u_int32_t fileSize = BytesToUInt32(&header[2]);
			u_int32_t dataOffset = BytesToUInt32(&header[10]);
			u_int32_t dibSize = BytesToUInt32(&header[14]);

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
			u_int8_t* dib = (u_int8_t*)malloc(sizeof(u_int8_t) * (dibSize - 4));
			if (dib == NULL) goto fail2;

			file.read((char*)dib, dibSize - 4);

			u_int32_t width = abs(BytesToInt32(&dib[18 - dibOffset]));
			u_int32_t height = abs(BytesToInt32(&dib[22 - dibOffset]));
			u_int16_t planes = BytesToUInt16(&dib[26 - dibOffset]);
			u_int16_t colorDepth = BytesToUInt16(&dib[28 - dibOffset]);
			u_int32_t compression = BytesToUInt32(&dib[30 - dibOffset]);
			u_int32_t rawSize = BytesToUInt32(&dib[34 - dibOffset]);
			int32_t hres = BytesToInt32(&dib[38 - dibOffset]);
			int32_t vres = BytesToInt32(&dib[42 - dibOffset]);
			u_int32_t colors = BytesToUInt32(&dib[46 - dibOffset]);
			
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
			u_int32_t format;

			if (colorDepth == 24)
				format = SDL_PIXELFORMAT_RGB24;
			else if (colorDepth == 32)
				format = SDL_PIXELFORMAT_RGBA32;

			u_int8_t* pixels = (u_int8_t*)malloc(sizeof(u_int8_t) * pitch * height);
			if (pixels == NULL) goto fail2;

			/*
			u_int8_t sample[4];
			u_int8_t a, r, g, b = 255;
			for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
					if (colorDepth == 24) {
						file.read((char*)sample, 3);

						b = sample[0];
						g = sample[1];
						r = sample[2];
						a = 255;
					} else if (colorDepth == 32) {
						file.read((char*)sample, 4);

						a = sample[0];
					}
				}

				//read padding
				if (colorDepth == 24) {
					int left = (width * 3) % 4;
					file.read((char*)sample, left);
				}
			}*/

			file.seekg(file._Seekbeg);
			file.read((char*)pixels, sizeof(u_int8_t) * pitch * height);

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

	}

}