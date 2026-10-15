#pragma once

#include <SDL3/SDL.h>
#include "renderer/Renderer2D.hpp"

struct SDL_Window;
struct SDL_Surface;

namespace gep
{
	class [[nodiscard]] game
	{
	public:
		[[nodiscard]] 
		auto init() noexcept -> bool;
		auto run() -> void;
		auto shutdown() noexcept -> void;

	private:
		SDL_Window* handle;
		SDL_Surface* image;
		SDL_GLContextState* gl_context = nullptr;

		Renderer2D renderer;
	};
}