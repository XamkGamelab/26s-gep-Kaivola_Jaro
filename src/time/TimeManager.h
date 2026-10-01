#pragma once
#include <SDL3/SDL.h>
#include <chrono>

union SDL_Event;

namespace gep::time
{

	class [[nodiscord]] Time
	{
	public:
		static auto Instance() -> Time&
		{
			static Time static_instance;
			return static_instance;
		}

		Time(const Time&) = delete;
		Time(Time&&) = delete;
		Time operator=(const Time&) = delete;
		Time operator=(Time&&) = delete;

		void Tick();
		float GetDeltaTime() const;

	private:
		Time() = default;
		~Time() = default;

		std::chrono::steady_clock::time_point previousTime{};
		float deltaTime = 0.0f;

	};
}