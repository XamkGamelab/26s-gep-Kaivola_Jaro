#include "input_system.hpp"
#include <SDL3/SDL.h>

auto gep::input::input_system::process_input(const SDL_Event&) -> void
{
	auto keycode = event.key.key;
	auto mouse_button_index = event.button.button;
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
	{
		keyDown.insert(keycode);
		keyPressed.insert(keycode);

		break;
	}

	case SDL_EVENT_KEY_UP:
	{

		keyUp.insert(keycode);
		keyPressed.erase(keycode);

		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{

		mouseDown.insert(mouse_button_index);
		mousePressed.insert(mouse_button_index);

		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_UP:
	{

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

auto::gep::input::input_system::IsKeyDown(SDL_Keycode key) noexcept -> void
{
	return keyDown.contains(key);
}

auto::gep::input::input_system::IsKeyUp(SDL_Keycode key) noexcept -> void
{
	return keyUp.contains(key);
}

auto::gep::input::input_system::IsKeyPressed(SDL_Keycode key) noexcept -> void
{
	return keyPressed.contains(key);
}

auto::gep::input::input_system::IsMouseDown(SDL_Keycode key) noexcept -> void
{
	return mouseDown.contains(key);
}

auto::gep::input::input_system::IsMouseUp(SDL_Keycode key) noexcept -> void
{
	return mouseUp.contains(key);
}

auto::gep::input::input_system::IsMousePressed(SDL_Keycode key) noexcept -> void
{
	return mousePressed.contains(key);
}
