#pragma once
#include <unordered_set>
#include <SDL3/SDL.h>

union SDL_Event;

namespace gep::input
{

	class [[nodiscord]] input_system
	{
	public:
		static auto instance() -> input_system&
		{
			static input_system static_instance;
			return static_instance;
		}

		input_system(const input_system&) = delete;
		input_system(input_system&&) = delete;
		input_system operator=(const input_system&) = delete;
		input_system operator=(input_system&&) = delete;


		auto Update() noexcept -> void;
		auto process_input(const SDL_Event&) -> void;

		auto IsKeyDown(uint32_t) const noexcept -> bool;
		auto IsKeyUp(uint32_t) const noexcept -> bool;
		auto IsKeyPressed(uint32_t) const noexcept -> bool;

		auto IsMouseDown(uint32_t) const noexcept -> bool;
		auto IsMouseUp(uint32_t) const noexcept -> bool;
		auto IsMousePressed(uint32_t) const noexcept -> bool;

	private:
		input_system() = default;
		~input_system() = default;

		std::unordered_set<SDL_Keycode> keyDown;
		std::unordered_set<SDL_Keycode> keyUp;
		std::unordered_set<SDL_Keycode> keyPressed;

		std::unordered_set<unsigned int> mouseDown;
		std::unordered_set<unsigned int> mouseUp;
		std::unordered_set<unsigned int> mousePressed;

	};
}