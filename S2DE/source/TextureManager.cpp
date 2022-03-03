#include "TextureManager.h"
#include "Window.h"
#include "Util.h"
#include "Core.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
			if (texture_table_count >= TEXTURE_TABLE_SIZE) {
				Console::LogCoreError("Run out of texture table memory!");
				printf("[S2DE] ERROR: Could not load file '%s'\n", path);
				return -1;
			}

			int hash = GetStringHash(path);
			int start = hash % TEXTURE_TABLE_SIZE;
			int index = start;

			int i = 0;
			while (texture_table[index] != NULL) {
				index = start + (i * i);
			}


			int wantedFormat = STBI_rgb_alpha;
			int width, height, originFormat;
			unsigned char* data = stbi_load(path, &width, &height, &originFormat, wantedFormat);
			if (data == NULL) {
				printf("[S2DE] ERROR: Could not load file '%s'\n", path);
				return -1;
			}

			int depth, pitch;
			Uint32 pixelFormat;
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
				printf("[S2DE] ERROR: Could not load file '%s'\n", path);
				return -1;
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);

			SDL_FreeSurface(surface);
			stbi_image_free(data);

			if (texture == NULL) {
				printf("[S2DE] ERROR: Could not load file '%s'\n", path);
				return -1;
			}

			texture_table[index] = texture;
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


		/*  My attempt at loading .bmp files. It worked, although the textures came out upside down. And I couldn't fix it :(
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

			if (colorDepth == 24) {
				//pitch = width * 3;
				format = SDL_PIXELFORMAT_RGB24;
			} else if (colorDepth == 32) {
				//pitch = width * 4;
				format = SDL_PIXELFORMAT_RGBA32;
			}

			u_int8_t* pixels = (u_int8_t*)malloc(sizeof(u_int8_t) * pitch * height);
			if (pixels == NULL) goto fail2;

			
			u_int8_t sample[3];
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

}