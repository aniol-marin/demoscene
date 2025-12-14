module;

#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>

module timer;

namespace MoleDemo
{
    using namespace mole_def;
    using ms = std::chrono::milliseconds;

    Timer::Timer() :
      frameCount{ 0 },
      secondCount{ 0 },
      frameTime{},
      deltaTime{},
      initialTime{ Clock::now() },
      previousTime{ Clock::now() }
    {
    }

    void Timer::SetNextFrameTime()
    {
        deltaTime = (milliseconds) std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - previousTime)
                            .count();
        previousTime = Clock::now();
        nextTime = Clock::now() + frameTime;
    }

    ms Timer::GetNextDelayTime() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(nextTime - Clock::now());
    }

    milliseconds Timer::GetDeltaTime() const
    {
        return deltaTime;
    }

    void Timer::SetFPS(uint_fast8_t fps)
    {
        frameTime = ms{ permilleFactor / fps };
    }

    void Timer::SetEndTime(seconds seconds)
    {
        endTime = initialTime + std::chrono::seconds(seconds);
    }

    void Timer::WaitUntilNextFrame()
    {
        std::this_thread::sleep_for(GetNextDelayTime());
        SetNextFrameTime();

        ++frameCount;
        secondCount = (seconds) std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - initialTime).count();

        if (secondCount > previousSecond)
        {
            previousSecond = secondCount;
            std::cout << "time [" << (int) previousSecond << "/"
                      << (int) (std::chrono::duration_cast<std::chrono::seconds>(endTime - initialTime).count())
                      << "],\t framerate: [" << (int) (frameCount) << "]fps,\t delta: [" << (int) deltaTime << "]\n";
            frameCount = 0;
        }
    }

    int_fast8_t Timer::GetTime() const
    {
        return secondCount;
    }

    bool Timer::EndReached() const
    {
        return Clock::now() >= endTime;
    }
}
