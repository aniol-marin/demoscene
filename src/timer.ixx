export module timer;

import <chrono>;
import <ratio>;
import <thread>;
// Debug
import <iostream>;
//!Debug

namespace MoleDemo {

	using Clock = std::chrono::steady_clock;
	export using Time = Clock::time_point;
	using ms = std::chrono::milliseconds;
	ms delay(Time since, Time until) {
		return std::chrono::duration_cast<std::chrono::milliseconds>(until - since);
	}
	export class Timer {

		ms frameTime;
		int_fast8_t previousSecond = 1;
		int_fast8_t secondCount;
		uint_fast32_t frameCount;
		uint_fast16_t deltaTime;
		Time initialTime;
		Time endTime;
		Time previousTime;
		Time nextTime;
		void SetNextFrameTime() {
			deltaTime = delay(previousTime, Clock::now()).count();
			previousTime = Clock::now();
			nextTime = Clock::now() + frameTime;
		}
		ms GetNextDelayTime() const {
			return  ms{ delay(nextTime ,Clock::now()) };
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
		uint16_t GetDeltaTime() const {
			return deltaTime;
		}
		void SetFPS(uint_fast8_t fps) {
			frameTime = ms{ 1000 / fps };
		}
		void SetEndTime(uint_fast8_t seconds) {
			endTime = initialTime + std::chrono::seconds(seconds);
		}
		void WaitUntilNextFrame() {
			auto timer = GetNextDelayTime();
			/*
			std::this_thread::sleep_for(GetNextDelayTime());
			*/
			SetNextFrameTime();
			++frameCount;
			secondCount = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - initialTime).count();

			if (secondCount > previousSecond) {
				previousSecond = secondCount;
				std::cout << "time [" << (int)previousSecond << "/" << (int)(std::chrono::duration_cast<std::chrono::seconds>(endTime - initialTime).count()) << "], framerate: [" << (int)(frameCount / previousSecond) << "]fps\n";
			}
		}
		int_fast8_t GetTime() const {
			return secondCount;
		}
		bool EndReached() const {
			return Clock::now() >= endTime;
		}
	};
}