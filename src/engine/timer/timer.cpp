#include "timer.h"

#include <chrono>
#include <iostream>
#include <thread>

using namespace mole_def;

void MoleDemo::Timer::SetNextFrameTime()
{
	deltaTime =
		(milliseconds)std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - previousTime).count();
	previousTime = Clock::now();
	nextTime = Clock::now() + frameTime;
}

ms MoleDemo::Timer::GetNextDelayTime() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(nextTime - Clock::now());
}

milliseconds MoleDemo::Timer::GetDeltaTime() const
{
	return deltaTime;
}

void MoleDemo::Timer::SetFPS(uint_fast8_t fps)
{
	frameTime = ms {permilleFactor / fps};
}

void MoleDemo::Timer::SetEndTime(seconds seconds)
{
	endTime = initialTime + std::chrono::seconds(seconds);
}

void MoleDemo::Timer::WaitUntilNextFrame()
{

	std::this_thread::sleep_for(GetNextDelayTime());
	SetNextFrameTime();

	++frameCount;
	secondCount = (seconds)std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - initialTime).count();

	if (secondCount > previousSecond)
	{
		previousSecond = secondCount;
		std::cout << "time [" << (int)previousSecond << "/"
				  << (int)(std::chrono::duration_cast<std::chrono::seconds>(endTime - initialTime).count())
				  << "],\t framerate: [" << (int)(frameCount) << "]fps,\t delta: [" << (int)deltaTime << "]\n";
		frameCount = 0;
	}
}

int_fast8_t MoleDemo::Timer::GetTime() const
{
	return secondCount;
}

bool MoleDemo::Timer::EndReached() const
{
	return Clock::now() >= endTime;
}
