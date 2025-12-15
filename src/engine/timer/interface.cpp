export module timer;

import std.compat;
import definitions;

namespace MoleDemo
{

    export class Timer;

    using Clock = std::chrono::steady_clock;
    using seconds = mole_def::seconds;
    using milliseconds = mole_def::milliseconds;
    using ms = std::chrono::milliseconds;
    export using Time = Clock::time_point;
}

class MoleDemo::Timer
{

    ms frameTime;
    seconds previousSecond = 0;
    seconds secondCount;
    uint_fast32_t frameCount;
    milliseconds deltaTime;
    Time initialTime;
    Time endTime;
    Time previousTime;
    Time nextTime;

    void SetNextFrameTime();
    ms GetNextDelayTime() const;

public:
    Timer();
    Timer(const Timer&) = delete ("a single instance is allowed, move it instead");
    Timer(Timer&&) = default;
    ~Timer() = default;

    milliseconds GetDeltaTime() const;
    void SetFPS(uint_fast8_t fps);
    void SetEndTime(seconds seconds);
    void WaitUntilNextFrame();
    int_fast8_t GetTime() const;
    bool EndReached() const;
};
