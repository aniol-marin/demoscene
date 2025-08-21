#ifndef MOLE_TIMER_H
#define MOLE_TIMER_H

#include <chrono>
#include <cstdint>

#include "definitions.h"

namespace MoleDemo
{
    using namespace mole_def;

    class Timer
    {
    public:
        using ms = std::chrono::milliseconds;
        using Clock = std::chrono::steady_clock;
        using Time = Clock::time_point;

    private:
        ms frameTime;
        seconds previousSecond{};
        seconds secondCount{};
        uint_fast32_t frameCount{};
        milliseconds deltaTime{};
        Time initialTime{ Clock::now() };
        Time endTime{};
        Time previousTime{ Clock::now() };
        Time nextTime{};

        void SetNextFrameTime();
        ms GetNextDelayTime() const;

    public:
        Timer();
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
} // namespace MoleDemo

#endif
