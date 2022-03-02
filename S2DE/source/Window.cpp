#include "S2DE.h"
#include "Window.h"
#include "TextureManager.h"
#include "Types.h"

#include <iostream>
#include <stddef.h>

namespace S2DE {

	namespace Window {

		const char* TITLE = "S2DE";

		const int CAMERA_WIDTH = 320;
		const int CAMERA_HEIGHT = 200;
		const int CAMERA_X_OFFSET = CAMERA_WIDTH / 2;
		const int CAMERA_Y_OFFSET = CAMERA_HEIGHT / 2;

		const int SCREEN_WIDTH = CAMERA_WIDTH*4;
		const int SCREEN_HEIGHT = CAMERA_HEIGHT*4;

		vec2f cameraPosition;

		bool hasInit;
		SDL_Window* window;
		SDL_Renderer* renderer;


		SDL_Renderer* GetRenderer() {
			return renderer;
		}


		int Init() {
			if (hasInit) return 0;

			if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				printf("[S2DE] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
				return 0;
			}

			window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL) {
				printf("[S2DE] Window could not be created! SDL_Error: %s\n", SDL_GetError());
				return 0;
			}

			/*
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("[S2DE] Failed to initialize texture loader! SDL_Error: %s\n", SDL_GetError());
				return 0;
			}
			*/

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("[S2DE] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 0;
			}

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
			SDL_RenderSetLogicalSize(renderer, CAMERA_WIDTH, CAMERA_HEIGHT);


			cameraPosition = *new vec2f(0, 0);

			hasInit = true;

			return 1;
		}


		void Clear() {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(renderer);
		}


		void Update() {
			SDL_RenderPresent(renderer);
		}


		void Close() {
			if (S2DE::IsRunning()) {
				S2DE::Close();
				return;
			}

			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);

			window = NULL;
			renderer = NULL;

			//IMG_Quit();
			SDL_Quit();
		}


		void ApplyTexture(Texture* texture, int x, int y) {
			SDL_Rect rect = { (CAMERA_X_OFFSET - (int)cameraPosition.x) + x, (CAMERA_Y_OFFSET + (int)cameraPosition.y) + y, texture->GetWidth(), texture->GetHeight() };
			SDL_Texture* tex = TextureManager::GetTextureData(texture->GetID());

			SDL_RenderCopy(renderer, tex, NULL, &rect);
		}

	}
}