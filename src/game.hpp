#pragma once

struct SDL_Window;

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
	};
}