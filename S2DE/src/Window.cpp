#include "Window.h"
#include "Core.h"
#include "Texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace S2DE;

const char* TITLE = "S2DE";

const int CAMERA_WIDTH = 320;
const int CAMERA_HEIGHT = 200;
const int CAMERA_X_OFFSET = CAMERA_WIDTH/2;
const int CAMERA_Y_OFFSET = CAMERA_HEIGHT/2;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

static vect cameraPosition;

static bool hasInit;
static SDL_Window* window;
static SDL_Renderer* renderer;

SDL_Renderer* Window::GetRenderer() {return renderer;}


int Window::Init() {
	if (hasInit) return -1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("[S2DE] SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("[S2DE] Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		printf("[S2DE] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return -1;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		printf("[S2DE] Failed to initialize texture loader! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_RenderSetLogicalSize(renderer, CAMERA_WIDTH, CAMERA_HEIGHT);

	cameraPosition = *new vect(0, 0);

	hasInit = true;

	return 0;
}

void Window::Clear() {
	SDL_RenderClear(renderer);
}

void Window::Update() {
	SDL_RenderPresent(renderer);
}

void Window::Close() {
	if (Core::IsRunning()) {
		Core::Close();
		return;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Window::ApplyTexture(Texture* texture, int x, int y) {
	SDL_Rect rect = { (CAMERA_X_OFFSET - (int)cameraPosition.x) + x, (CAMERA_Y_OFFSET + (int)cameraPosition.y) + y, texture->GetWidth(), texture->GetHeight() };
	SDL_RenderCopy(renderer, texture->GetSDL(), NULL, &rect);
}

Texture* Window::LoadTexture(std::string path) {
	Texture* texture = new Texture();
	texture->Load(path);

	return texture;
}
