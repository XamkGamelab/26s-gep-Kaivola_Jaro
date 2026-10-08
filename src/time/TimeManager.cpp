#include "TimeManager.h"
#include <chrono>
#include <iostream>
#include <algorithm>

namespace gep::time
{
	auto Time::Tick() noexcept -> void
	{
		using clock = std::chrono::steady_clock;
		const auto currentTime = clock::now();

		if (firstTick)
		{
			previousTime = currentTime;
			deltaTime = 0.0f;
			firstTick = false;
			return;
		}

		const std::chrono::duration<float> elapsed = currentTime - previousTime;
		previousTime = currentTime;
		deltaTime = std::min(elapsed.count(), 1.0f / 30.0f);
		std::cout << deltaTime << "\n";
	}

	auto Time::GetDeltaTime() const noexcept -> float
	{
		return deltaTime;
	}
}