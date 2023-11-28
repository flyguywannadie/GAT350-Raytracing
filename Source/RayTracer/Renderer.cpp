#include "Canvas.h"
#include "Renderer.h"
#include <iostream>

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::PresentCanvas(const Canvas& canvas)
{
	// copy canvas texture to renderer
	SDL_RenderCopy(renderer, canvas.m_texture, NULL, NULL);
	// present renderer to screen
	SDL_RenderPresent(renderer);
}