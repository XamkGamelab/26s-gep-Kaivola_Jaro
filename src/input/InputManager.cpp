#include "InputManager.h"

InputManager& InputManager::Instance()
{
	static InputManager instance;
	return instance;
}

void InputManager::ProcessEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_EVENT_KEY_DOWN:
	{
		SDL_Keycode key = event.key.key;

		m_keyDown.insert(key);
		m_keyPressed.insert(key);

		break;
	}

	case SDL_EVENT_KEY_UP:
	{
		SDL_Keycode key = event.key.key;

		m_keyUp.insert(key);
		m_keyPressed.erase(key);

		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{
		unsigned int button = event.button.button;

		m_mouseDown.insert(button);
		m_mousePressed.insert(button);

		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_UP:
	{
		unsigned int button = event.button.button;

		m_mouseUp.insert(button);
		m_mousePressed.erase(button);

		break;
	}

	default:
		break;
	}
}

void InputManager::Update()
{
	m_keyDown.clear();
	m_keyUp.clear();

	m_mouseDown.clear();
	m_mouseUp.clear();
}

bool InputManager::IsKeyDown(SDL_Keycode key)
{
	return m_keyDown.contains(key);
}

bool InputManager::IsKeyUp(SDL_Keycode key)
{
	return m_keyUp.contains(key);
}

bool InputManager::IsKeyPressed(SDL_Keycode key)
{
	return m_keyPressed.contains(key);
}

bool InputManager::IsMouseDown(unsigned int mouseBtnIdx)
{
	return m_mouseDown.contains(mouseBtnIdx);
}

bool InputManager::IsMouseUp(unsigned int mouseBtnIdx)
{
	return m_mouseUp.contains(mouseBtnIdx);
}

bool InputManager::IsMousePressed(unsigned int mouseBtnIdx)
{
	return m_mousePressed.contains(mouseBtnIdx);
}