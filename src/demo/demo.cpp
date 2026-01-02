#include "demo.h"

#include <iostream>
#include <string>
#include <typeinfo>

namespace MoleDemo
{
    using namespace mole_def;

    void Demo::LoadData(std::string source) {}

    void Demo::LoadTimeline(std::string source) {}

    void Demo::Load(std::string source)
    {
        if (!loadables.empty())
        {
            for (Loadable* item = *loadables.begin(); item != *loadables.end(); ++item)
            {
                item->Load(source);
            }
        }
    }

    void Demo::Unload()
    {
        if (!loadables.empty())
        {
            for (Loadable* item = *loadables.begin(); item != *loadables.end(); ++item)
            {
                item->Unload();
            }
        }
    }

    void Demo::Init()
    {
        InstallBindings();

        /*
                initializables.push_back(&container.Inject<RenderManager>());
                initializables.push_back(timeline);
                initializables.push_back(sound);

                loadables.push_back(timeline);
                loadables.push_back(sound);
        */

        timer->SetFPS(60);

        if (!initializables.empty())
        {
            for (Initializable* item = *initializables.begin(); item != *initializables.end(); ++item)
            {
                item->Init();
            }
        }

        Load(source);
    }

    void Demo::Finalize()
    {
        Unload();

        if (!initializables.empty())
        {
            for (Initializable* item = *initializables.begin(); item != *initializables.end(); ++item)
            {
                item->Finalize();
            }
        }
    }

    void Demo::InstallBindings()
    {
        /*
        container.BindShared<Timer>();
        container.BindShared<SoundManager>();
        container.BindShared<Screen>([this] { return new Screen{ this->screen }; });
        container.BindShared<Program>([&] { return new Program{ container.Inject<Screen>() }; });
        container.BindShared<SDL::SDLManager>();
        container.BindShared<RenderManager>(
                [&] { return new RenderManager{ container.Inject<Screen>(), container.Inject<SDL::SDLManager>() }; });
        container.BindShared<InputManager>([&] { return new InputManager{ container.Inject<SDL::SDLManager>() }; });
        container.BindShared<Cycle>(
                [&]
                {
                    return new Cycle{ container.Inject<Program>(),
                                      container.Inject<Timer>(),
                                      container.Inject<InputManager>(),
                                      container.Inject<RenderManager>() };
                });
        container.BindShared<Timeline>(
                [&]
                {
                    return new Timeline{ container.Inject<Timer>(),  container.Inject<Program>(),
                                         container.Inject<Cycle>(),  container.Inject<SoundManager>(),
                                         container.Inject<Screen>(), project };
                });
         */
        /* TODO replace manual functor resolution with in-place factories. Examples follow:
           container.BindUniqueFromFactory<Cycle, Cycle, Program, Timer, InputManager, RenderManager>();
           container.BindSharingFromFactory<Timeline, Timeline, Timer, Cycle, SoundManager, Screen>();
           */

        // Self injection (TO DO separate concerns)

        /*
                program = &container.Inject<Program>();
                timer = &container.Inject<Timer>();
                sound = &container.Inject<SoundManager>();
                timeline = &container.Inject<Timeline>();
        */
    }

    Demo::Demo(std::string project) : screen(600, 300), project(project), source(), container() {}

    void Demo::Run()
    {
        seconds previous_time;

        Init();
        /*
            sound->Play();
            timeline->Start();

            while (program->Running())
            {
                sound->Update();
                timeline->Update();

                const seconds current_time = timer->GetTime();
                if (current_time > previous_time)
                {
                    std::cout //
                            << "time [" << current_time << "/" << timer->get_total_time() //
                            << "],\t framerate: [" << timer->get_frames_since_mark() //
                            << "], fps,\t delta: [" << timer->GetDeltaTime() << "]\n";
                    timer->set_mark();
                    previous_time = current_time;
                }
            }

            sound->Stop();
            timeline->Stop();
         */
        Finalize();
    }
}
