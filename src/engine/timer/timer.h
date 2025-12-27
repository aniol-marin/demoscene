#ifndef MOLE_TIMER_H
#define MOLE_TIMER_H

#include <ctime>

#include "definitions.h"

namespace MoleDemo
{
    class Timer;

    /*
    using clock_t = std::chrono::steady_clock;
    using time_t = clock_t::time_point;

    using frame_t = std::uint_fast32_t;
    using mole_s = mole_def::seconds;
    using mole_ms = mole_def::milliseconds;
    using ms = std::chrono::milliseconds;
     */
    typedef unsigned char fps_t;
    typedef long unsigned int ms;
    typedef long unsigned int time_t;
    typedef long unsigned int frame_t;
    typedef long unsigned int mole_ms;
    typedef long unsigned int mole_s;
    typedef std::clock_t clock_t;
}

class MoleDemo::Timer
{
    const time_t initial_time;
    time_t last_time;
    time_t last_mark;
    mole_ms delta_time;
    ms frameTime;

    time_t endTime;
    frame_t frames_since_mark;

    void update_frame_level_state();
    ms get_next_time_target() const;

public:
    Timer();
    Timer(const Timer&);
    ~Timer();

    mole_ms GetDeltaTime() const;
    void SetFPS(fps_t fps);
    void SetEndTime(mole_s mole_s);
    void set_mark();
    void WaitUntilNextFrame();
    mole_s GetTime() const;
    bool EndReached() const;
    mole_s get_total_time() const;
    frame_t get_frames_since_mark() const;
};

#endif
