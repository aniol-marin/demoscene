module demo;

import engine;

namespace MoleDemo
{
    using namespace mole_def;

    application::application(Screen& screen,
                             RenderManager& render,
                             SoundManager& sound,
                             Timeline& timeline,
                             Timer& timer,
                             Program& program) :
      screen{ screen }, render{ render }, sound{ sound }, timeline{ timeline }, timer{ timer }, program{ program }
    {
    }

    void application::run()
    {
        seconds previous_time{};
        timer.SetFPS(60); // TO DO timer invariant, split into timer and synchronizer

        sound.Play();
        timeline.Start();

        while (program.Running())
        {
            sound.Update();
            timeline.Update();

            if (const seconds current_time{ timer.GetTime() }; current_time > previous_time)
            {
                std::cout //
                        << "time [" << current_time << "/" << timer.get_total_time() //
                        << "],\t framerate: [" << timer.get_frames_since_mark() //
                        << "], fps,\t delta: [" << timer.GetDeltaTime() << "]\n";
                timer.set_mark();
                previous_time = current_time;
            }
        }

        sound.Stop();
    }
}
