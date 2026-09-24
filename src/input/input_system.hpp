#pragma once

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

		auto process_input(const SDL_Event&) -> void;

	private:
		input_system() = default;
		~input_system() = default;

	};
}