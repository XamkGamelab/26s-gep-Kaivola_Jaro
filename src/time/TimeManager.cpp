#include "TimeManager.h"
#include <chrono>
#include <iostream>

namespace gep::time
{
	void Time::Tick()
	{
		using clock = std::chrono::steady_clock;
		const auto currentTime = clock::now();
		const std::chrono::duration<float> elapsed = currentTime - previousTime;
		previousTime = currentTime;
		deltaTime = std::min(elapsed.count(), 1.0f / 30.0f);
		std::cout << deltaTime << "\n";
	}

	float Time::GetDeltaTime() const
	{
		return deltaTime;
	}
}