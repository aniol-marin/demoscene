#include "timer.h"
#include <exception>

namespace
{
    // temporary mocking
    long long g_fake_framecount = 0;
}

namespace MoleDemo
{
    /* TO DO function template aliases
     * wishful in pseudo:
     using ms_cast = static_cast<milliseconds>;
     using s_cast = static_cast<seconds>;
     using ms_duration_cast = std::chrono::duration_cast<std::chrono::milliseconds>;
     using s_duration_cast = std::chrono::duration_cast<std::chrono::seconds>;

     * found untested solution:
     template<typename... Args>
     auto wrapper(Args&&... args) -> decltype(function(std::forward<Args>(args)...))
     {
     return function(std::forward<Args>(args)...);
     }
    using namespace mole_def;
    using mole_ms = mole_def::milliseconds;
    using mole_s = mole_def::seconds;
    using s = std::chrono::seconds;
    */

    Timer::Timer() : initial_time(), last_time(), last_mark(), delta_time(), frameTime()
    /*
    : initial_time{ clock_t::now() }
    , last_time{ initial_time }
    , last_mark{ initial_time }
     */
    {
    }

    Timer::Timer(const Timer&) : initial_time(), last_time(), last_mark(), delta_time(), frameTime()
    {
        throw std::exception();
    }

    Timer::~Timer() {}

    void Timer::update_frame_level_state()
    {
        ++g_fake_framecount;
        time_t current_time = g_fake_framecount / 60;

        /*
        time_t current_time{ clock_t::now() };
        delta_time = static_cast<mole_ms>(std::chrono::duration_cast<ms>(current_time - last_time).count());
         */
        last_time = current_time;
        ++frames_since_mark;
    }

    ms Timer::get_next_time_target() const
    {
        /*
        return std::chrono::duration_cast<std::chrono::milliseconds>(last_time + frameTime - clock_t::now());
    */
        return 0;
    }

    mole_ms Timer::GetDeltaTime() const
    {
        return delta_time;
    }

    mole_s Timer::get_total_time() const
    {
        /*
        return static_cast<seconds>(std::chrono::duration_cast<std::chrono::seconds>(endTime - initial_time).count());
         */
        return g_fake_framecount / 60;
    }

    void Timer::SetFPS(fps_t fps)
    {
        frameTime = static_cast<ms>(mole_def::permilleFactor() / fps);
    }

    void Timer::SetEndTime(mole_s seconds)
    {
        endTime = seconds;
        /*
            endTime = initial_time + std::chrono::seconds(seconds);
        */
    }

    void Timer::WaitUntilNextFrame()
    {
        /*
        std::this_thread::sleep_for(get_next_time_target());
        update_frame_level_state();
         */
    }

    void Timer::set_mark()
    {
        frames_since_mark = 0;
        last_mark = g_fake_framecount;
        /*
            last_mark = { clock_t::now() };
         */
    }

    mole_s Timer::GetTime() const
    {
        /*
        return static_cast<mole_s>(std::chrono::duration_cast<s>(last_time - initial_time).count());
         */
        return g_fake_framecount / 60;
    }

    bool Timer::EndReached() const
    {

        /*
        return clock_t::now() >= endTime;
         */
        return (g_fake_framecount / 60) >= endTime;
    }

    frame_t Timer::get_frames_since_mark() const
    {
        return frames_since_mark;
    }
}
