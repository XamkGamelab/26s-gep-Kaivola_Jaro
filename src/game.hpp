#pragma once

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
	};
}