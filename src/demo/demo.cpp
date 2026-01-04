#include "demo.h"

#include <string>

namespace
{
    using namespace mole_def;
    using namespace MoleDemo;

    static Container container = Container();
    static Screen screen = Screen(0, 0);
    static std::string project = std::string();
}
namespace MoleDemo
{
    using namespace mole_def;

    void Demo::LoadData(std::string source) {}

    void Demo::LoadTimeline(std::string source) {}

    void Demo::Load(std::string source)
    {
        if (!loadables.empty())
        {
            for (std::vector<Loadable*>::iterator item = loadables.begin(); item != loadables.end(); ++item)
            {
                (*item)->Load(source);
            }
        }
    }

    void Demo::Unload()
    {
        if (!loadables.empty())
        {
            for (std::vector<Loadable*>::iterator item = loadables.begin(); item != loadables.end(); ++item)
            {
                (*item)->Unload();
            }
        }
    }

    void Demo::Init()
    {
        InstallBindings();

        initializables.push_back(&container.Inject<RenderManager>());
        initializables.push_back(sound);
        initializables.push_back(timeline);

        loadables.push_back(sound);
        loadables.push_back(timeline);

        timer->SetFPS(60);

        if (!initializables.empty())
        {
            for (std::vector<Initializable*>::iterator item = initializables.begin(); item != initializables.end();
                 ++item)
            {
                (*item)->Init();
            }
        }

        Load(source);
    }

    void Demo::Finalize()
    {
        Unload();

        if (!initializables.empty())
        {
            for (std::vector<Initializable*>::iterator item = initializables.begin(); item != initializables.end();
                 ++item)
            {
                (*item)->Finalize();
            }
        }
    }

    void* instantiate_timer()
    {
        return static_cast<void*>(new Timer());
    }

    void* instantiate_screen()
    {
        return static_cast<void*>(new mole_def::Screen(screen));
    }

    void* instantiate_program()
    {
        return static_cast<void*>(new Program(container.Inject<Screen>()));
    }

    void* instantiate_render_manager()
    {
        return static_cast<void*>(new RenderManager(container.Inject<Screen>(), container.Inject<SDL::SDLManager>()));
    }

    void* instantiate_input_manager()
    {
        return static_cast<void*>(new InputManager(container.Inject<SDL::SDLManager>()));
    }

    void* instantiate_cycle()
    {
        return static_cast<void*>(new Cycle(container.Inject<Program>(),
                                            container.Inject<Timer>(),
                                            container.Inject<InputManager>(),
                                            container.Inject<RenderManager>()));
    }

    void* instantiate_sound_manager()
    {
        return static_cast<void*>(new SoundManager());
    }

    void* instantiate_timeline()
    {
        return static_cast<void*>(new Timeline(container.Inject<Timer>(),
                                               container.Inject<Program>(),
                                               container.Inject<Cycle>(),
                                               container.Inject<SoundManager>(),
                                               container.Inject<Screen>(),
                                               project));
    }

    void Demo::InstallBindings()
    {
        container.BindShared<Timer>();
        container.BindShared<SoundManager>();
        container.BindShared<Screen>(instantiate_screen);
        container.BindShared<Program>(instantiate_program);
        container.BindShared<SDL::SDLManager>();
        container.BindShared<RenderManager>(instantiate_render_manager);
        container.BindShared<InputManager>(instantiate_input_manager);
        container.BindShared<SoundManager>(instantiate_sound_manager);
        container.BindShared<Cycle>(instantiate_cycle);
        container.BindShared<Timeline>(instantiate_timeline);

        /* TODO replace manual functor resolution with in-place factories. Examples follow:
    container.BindUniqueFromFactory<Cycle, Cycle, Program, Timer, InputManager, RenderManager>();
    container.BindSharingFromFactory<Timeline, Timeline, Timer, Cycle, SoundManager, Screen>();
    */

        // Self injection (TO DO separate concerns)
        timer = &container.Inject<Timer>();
        program = &container.Inject<Program>();
        sound = &container.Inject<SoundManager>();
        timeline = &container.Inject<Timeline>();
    }

    Demo::Demo(std::string a_project) : source()
    {
        screen = Screen(600, 300);
        project = std::string(a_project);
    }

    void Demo::Run()
    {
        seconds previous_time;

        Init();
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
        Finalize();
    }
}
