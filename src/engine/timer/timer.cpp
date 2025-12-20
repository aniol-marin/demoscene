module;

#include <chrono>
#include <thread>
#include <cstdint>

module timer;

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
     */
    using namespace mole_def;
    using mole_ms = mole_def::milliseconds;
    using mole_s = mole_def::seconds;
    using s = std::chrono::seconds;

    Timer::Timer() :
      initial_time{ clock_t::now() }, //
      last_time{ initial_time },
      last_mark{ initial_time }
    {
    }

    void Timer::update_frame_level_state()
    {
        time_t current_time{ clock_t::now() };
        delta_time = static_cast<mole_ms>(std::chrono::duration_cast<ms>(current_time - last_time).count());
        last_time = current_time;
        ++frames_since_mark;
    }

    ms Timer::get_next_time_target() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(last_time + frameTime - clock_t::now());
    }

    milliseconds Timer::GetDeltaTime() const
    {
        return delta_time;
    }

    seconds Timer::get_total_time() const
    {
        return static_cast<seconds>(std::chrono::duration_cast<std::chrono::seconds>(endTime - initial_time).count());
    }

    void Timer::SetFPS(std::uint_fast8_t fps)
    {
        frameTime = ms{ permilleFactor / fps };
    }

    void Timer::SetEndTime(seconds seconds)
    {
        endTime = initial_time + std::chrono::seconds(seconds);
    }

    void Timer::WaitUntilNextFrame()
    {
        std::this_thread::sleep_for(get_next_time_target());
        update_frame_level_state();
    }

    void Timer::set_mark()
    {
        frames_since_mark = {};
        last_mark = { clock_t::now() };
    }

    mole_s Timer::GetTime() const
    {
        return static_cast<mole_s>(std::chrono::duration_cast<s>(last_time - initial_time).count());
    }

    bool Timer::EndReached() const
    {
        return clock_t::now() >= endTime;
    }

    frame_t Timer::get_frames_since_mark() const
    {
        return frames_since_mark;
    }
}
