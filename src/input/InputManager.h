#pragma once
#include <SDL3/SDL.h>
#include <unordered_set>

class InputManager
{
public:

	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static InputManager& Instance();

	void ProcessEvent(const SDL_Event& event);
	void Update();

	bool IsKeyDown(SDL_Keycode key);
	bool IsKeyUp(SDL_Keycode key);
	bool IsKeyPressed(SDL_Keycode key);

	bool IsMouseDown(unsigned int mouseBtnIdx);
	bool IsMouseUp(unsigned int mouseBtnIdx);
	bool IsMousePressed(unsigned int mouseBtnIdx);

private:

	std::unordered_set<SDL_Keycode> m_keyDown;
	std::unordered_set<SDL_Keycode> m_keyUp;
	std::unordered_set<SDL_Keycode> m_keyPressed;

	std::unordered_set<unsigned int> m_mouseDown;
	std::unordered_set<unsigned int> m_mouseUp;
	std::unordered_set<unsigned int> m_mousePressed;

	InputManager() = default;
	~InputManager() = default;

};