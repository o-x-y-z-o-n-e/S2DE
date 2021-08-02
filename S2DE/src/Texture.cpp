#include "Texture.h"
#include "Window.h"

#include <SDL2/SDL_image.h>

using namespace S2DE;

Texture::Texture() {
    sdl_texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    Free();
}

bool Texture::Load(std::string path) {
    Free();

    SDL_Texture* texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load (path.c_str());
	if(loadedSurface == NULL) {
		printf("[S2DE] Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	} else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(Window::GetRenderer(), loadedSurface);
    	if(texture == NULL) {
            printf("[S2DE] Unable to load texture %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    sdl_texture = texture;
    return sdl_texture != NULL;
}

void Texture::Free() {
    width = 0;
    height = 0;
    if(sdl_texture == NULL) return;
    SDL_DestroyTexture(sdl_texture);
    sdl_texture = NULL;
}

int Texture::GetWidth() { return width; }
int Texture::GetHeight() { return height; }
SDL_Texture* Texture::GetSDL() { return sdl_texture; }
