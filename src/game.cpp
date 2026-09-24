#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_Log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <iostream>
#include <SDL3/SDL_surface.h>
#include "input/InputManager.h"
#include "SDL3_image/SDL_image.h"

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

	image = IMG_Load("assets/awesomeface.png");

	if (image == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"IMG_Load failed: %s", SDL_GetError());

		return false;
	}

	return true;
}

auto gep::game::run() -> void
{
	auto& inputManager = InputManager::Instance();

	bool is_running = true;

	int image_x = 0;
	int image_y = 0;
	const int speed = 5;

	SDL_Surface* window_surface = SDL_GetWindowSurface(handle);

	if (window_surface != nullptr && image != nullptr)
	{
		image_x = (window_surface->w - image->w) / 2;
		image_y = (window_surface->h - image->h) / 2;
	}

	while (is_running)
	{

		inputManager.Update();

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				is_running = false;
			}

			if (event.type == SDL_EVENT_KEY_DOWN &&
				event.key.key == SDLK_ESCAPE)
			{
				is_running = false;
			}

			inputManager.ProcessEvent(event);
		}

		window_surface = SDL_GetWindowSurface(handle);

		if (window_surface == nullptr || image == nullptr)
		{
			continue;
		}

		if (inputManager.IsKeyPressed(SDLK_W))
		{
			image_y -= speed;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 215, 0, 64));
		}

		if (inputManager.IsKeyPressed(SDLK_A))
		{
			image_x -= speed;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 11, 218, 81));
		}

		if (inputManager.IsKeyPressed(SDLK_S))
		{
			image_y += speed;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 4, 55, 242));
		}

		if (inputManager.IsKeyPressed(SDLK_D))
		{
			image_x += speed;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 255, 215, 0));
		}

		if (image_x < 0)
		{
			image_x = 0;
		}

		if (image_y < 0)
		{
			image_y = 0;
		}

		if (image_x + image->w > window_surface->w)
		{
			image_x = window_surface->w - image->w;
		}

		if (image_y + image->h > window_surface->h)
		{
			image_y = window_surface->h - image->h;
		}

		SDL_Rect position{image_x, image_y, image->w, image->h};

		SDL_BlitSurface(image, nullptr, window_surface, &position);

		SDL_UpdateWindowSurface(handle);
	}
}

auto gep::game::shutdown() noexcept -> void
{
	if (image != nullptr)
	{
		SDL_DestroySurface(image);
	}

	if (handle != nullptr)
	{
		SDL_DestroyWindow(handle);
	}

	SDL_Quit();
}