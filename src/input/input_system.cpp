#include "input_system.hpp"
#include <SDL3/SDL.h>

auto gep::input::input_system::process_input(const SDL_Event& event) -> void
{

	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
	{
		auto keycode = event.key.key;

		keyDown.insert(keycode);
		keyPressed.insert(keycode);

		break;
	}

	case SDL_EVENT_KEY_UP:
	{
		auto keycode = event.key.key;

		keyUp.insert(keycode);
		keyPressed.erase(keycode);

		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{
		auto mouse_button_index = event.button.button;

		mouseDown.insert(mouse_button_index);
		mousePressed.insert(mouse_button_index);

		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_UP:
	{
		auto mouse_button_index = event.button.button;

		mouseUp.insert(mouse_button_index);
		mousePressed.erase(mouse_button_index);

		break;
	}

	default:
		break;
	}
}

auto gep::input::input_system::Update() noexcept -> void
{
	keyDown.clear();
	keyUp.clear();

	mouseDown.clear();
	mouseUp.clear();
}

auto gep::input::input_system::IsKeyDown(SDL_Keycode key) const noexcept -> bool
{
	return keyDown.contains(key);
}


auto gep::input::input_system::IsKeyUp(SDL_Keycode key) const noexcept -> bool
{
	return keyUp.contains(key);
}

auto::gep::input::input_system::IsKeyPressed(SDL_Keycode key) const noexcept -> bool
{
	return keyPressed.contains(key);
}

auto gep::input::input_system::IsMouseDown(uint32_t button) const noexcept -> bool
{
	return mouseDown.contains(button);
}

auto gep::input::input_system::IsMouseUp(uint32_t button) const noexcept -> bool
{
	return mouseUp.contains(button);
}

auto gep::input::input_system::IsMousePressed(uint32_t button) const noexcept -> bool
{
	return mousePressed.contains(button);
}
