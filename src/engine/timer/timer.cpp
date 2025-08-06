#include "timer.h"

#include <iostream>
#include <thread>

namespace MoleDemo
{
    using namespace mole_def;

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
        secondCount = static_cast<seconds>(
                std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - initialTime).count());

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

    Timer::ms Timer::GetNextDelayTime() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(nextTime - Clock::now());
    }

    void Timer::SetNextFrameTime()
    {
        deltaTime = static_cast<mole_def::milliseconds>(
                std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - previousTime).count());
        previousTime = Clock::now();
        nextTime = Clock::now() + frameTime;
    }

}
