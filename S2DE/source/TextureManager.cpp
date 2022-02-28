#include "TextureManager.h"
#include "Window.h"
#include "Util.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace S2DE {

    SDL_Texture* texture_table[TEXTURE_TABLE_SIZE];
    int texture_table_count = 0;


    void InitTextureManager() {
        
    }


    int LoadTextureData(const char* path) {
        if(texture_table_count >= TEXTURE_TABLE_SIZE)
            return 0;

        int hash = GetStringHash(path);
        int start = hash % TEXTURE_TABLE_SIZE;
        int index = start;

        int i = 0;
        while (texture_table[index] != NULL) {
            index = start + (i*i);
        }

        
        SDL_Surface* surface = IMG_Load(path);
        if(surface == NULL)
            return 0;

        texture_table[index] = SDL_CreateTextureFromSurface(Window::GetRenderer(), surface);
        texture_table_count++;

        SDL_FreeSurface(surface);

        return index;
    }


    void FreeTextureData(int id) {
        if(texture_table[id] == NULL)
            return;
        
        SDL_DestroyTexture(texture_table[id]);
        texture_table[id] = NULL;
        texture_table_count--;
    }


    SDL_Texture* GetTextureData(int id) {
        return texture_table[id];
    }

}