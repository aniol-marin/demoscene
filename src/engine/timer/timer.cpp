module;

#include <cstdint>

export module timer;

import std;
import definitions;

namespace MoleDemo {

	export class Timer;

	using Clock = std::chrono::steady_clock;
	using ms = std::chrono::milliseconds;
	export using Time = Clock::time_point;
}

class MoleDemo::Timer {

	ms frameTime;
	seconds previousSecond = 0;
	seconds secondCount;
	uint_fast32_t frameCount;
	milliseconds deltaTime;
	Time initialTime;
	Time endTime;
	Time previousTime;
	Time nextTime;
	void SetNextFrameTime() {
		deltaTime = (milliseconds)std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - previousTime).count();
		previousTime = Clock::now();
		nextTime = Clock::now() + frameTime;
	}
	ms GetNextDelayTime() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(nextTime - Clock::now());
	}
public:
	Timer() :
		frameCount{ 0 },
		secondCount{ 0 },
		frameTime{},
		deltaTime{},
		initialTime{ Clock::now() },
		previousTime{ Clock::now() }
	{}
	milliseconds GetDeltaTime() const {
		return deltaTime;
	}
	void SetFPS(uint_fast8_t fps) {
		frameTime = ms{ permilleFactor / fps };
	}
	void SetEndTime(seconds seconds) {
		endTime = initialTime + std::chrono::seconds(seconds);
	}
	void WaitUntilNextFrame() {

		std::this_thread::sleep_for(GetNextDelayTime());
		SetNextFrameTime();

		++frameCount;
		secondCount = (seconds)std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - initialTime).count();

		if (secondCount > previousSecond) {
			previousSecond = secondCount;
			std::cout << "time [" << (int)previousSecond << "/" << (int)(std::chrono::duration_cast<std::chrono::seconds>(endTime - initialTime).count()) << "],\t framerate: [" << (int)(frameCount) << "]fps,\t delta: [" << (int)deltaTime << "]\n";
			frameCount = 0;
		}
	}
	int_fast8_t GetTime() const {
		return secondCount;
	}
	bool EndReached() const {
		return Clock::now() >= endTime;
	}
};
