#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_Log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <iostream>
#include <SDL3/SDL_surface.h>

auto gep::game::init() noexcept -> bool
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
			"SDL_Init failed: %s", SDL_GetError());

		return false;
	}

	handle = SDL_CreateWindow("GEP", 1280, 720, SDL_WINDOW_RESIZABLE);
	if (handle == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
			"SDL_CreateWindow failed: %s", SDL_GetError());
		return false;
	}

	return true;
}

auto gep::game::run() -> void
{
	bool is_running = true;
	while (is_running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				is_running = false;
			}

			if (event.key.key == SDLK_ESCAPE) {
				is_running = false;
			}

			if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				std::cout << "Resized window" << std::endl;
			}

			if (event.key.key == SDLK_W)
			{
				SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
					SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 215, 0, 64));
				SDL_UpdateWindowSurface(handle);
			}
			
			if (event.key.key == SDLK_A)
			{
				SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
					SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 11, 218, 81));
				SDL_UpdateWindowSurface(handle);
			}

			if (event.key.key == SDLK_S)
			{
				SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
					SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 4, 55, 242));
				SDL_UpdateWindowSurface(handle);
			}

			if (event.key.key == SDLK_D)
			{
				SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
					SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 255, 215, 0));
				SDL_UpdateWindowSurface(handle);
			}
		}
	}
}

auto gep::game::shutdown() noexcept -> void
{
	if (handle != nullptr)
	{
		SDL_DestroyWindow(handle);
	}

	SDL_Quit();
}