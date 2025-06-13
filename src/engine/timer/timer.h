#include <chrono>

#include "definitions.h"

namespace
{
	using Clock = std::chrono::steady_clock;
	using ms = std::chrono::milliseconds;
} // namespace

namespace MoleDemo
{
	using namespace mole_def;

	class Timer;
	using Time = Clock::time_point;
} // namespace MoleDemo

class MoleDemo::Timer
{

	ms frameTime;
	seconds previousSecond {};
	seconds secondCount {};
	uint_fast32_t frameCount {};
	milliseconds deltaTime {};
	Time initialTime {Clock::now()};
	Time endTime {};
	Time previousTime {Clock::now()};
	Time nextTime {};

	void SetNextFrameTime();
	ms GetNextDelayTime() const;

  public:

	Timer() = default;
	Timer(const Timer&) = delete;
	Timer(Timer&&) = default;
	~Timer() = default;

	milliseconds GetDeltaTime() const;
	void SetFPS(uint_fast8_t fps);
	void SetEndTime(seconds seconds);
	void WaitUntilNextFrame();
	int_fast8_t GetTime() const;
	bool EndReached() const;
};
