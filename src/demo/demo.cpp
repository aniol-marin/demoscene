module demo;

import engine;

namespace MoleDemo
{
    using namespace mole_def;

    Demo::Demo(std::string project)
    {
        // TO DO load values from config string
    }

    void Demo::Run()
    {
        std::string project{}; // TO DO get values from constructor maybe
        Init(project);

        container.Inject<application>().run();
        /*
            application& application{ container.Inject<application>() };
            application.run();
        */

        Finalize();
    }

    void Demo::Init(std::string& project)
    {
        InstallBindings(project);

        // TO DO automatic interface detection
        initializables.push_back(&container.Inject<RenderManager>());
        initializables.push_back(&container.Inject<Timeline>());
        initializables.push_back(&container.Inject<SoundManager>());
        for (Initializable* item: initializables)
        {
            item->Init();
        }

        loadables.push_back(&container.Inject<Timeline>());
        loadables.push_back(&container.Inject<SoundManager>());
        for (Loadable* item: loadables)
        {
            item->Load(project);
        }
    }

    void Demo::Finalize()
    {
        for (Loadable* item: loadables)
        {
            item->Unload();
        }
        for (Initializable* item: initializables)
        {
            item->Finalize();
        }
    }

    void Demo::InstallBindings(std::string& project)
    {
        container.BindShared<Timer>();
        container.BindShared<SoundManager>();
        container.BindShared<Screen>([this] { return Screen{ 600, 300 }; }); // TO DO get from config
        container.BindShared<Program>([&] { return Program{ container.Inject<Screen>() }; });
        container.BindShared<SDL::SDLManager>();
        container.BindShared<RenderManager>(
                [&] { return RenderManager{ container.Inject<Screen>(), container.Inject<SDL::SDLManager>() }; });
        container.BindShared<InputManager>([&] { return InputManager{ container.Inject<SDL::SDLManager>() }; });
        container.BindShared<Cycle>(
                [&]
                {
                    return Cycle{ container.Inject<Program>(),
                                  container.Inject<Timer>(),
                                  container.Inject<InputManager>(),
                                  container.Inject<RenderManager>() };
                });
        container.BindShared<Timeline>(
                [&]
                {
                    return Timeline{ container.Inject<Timer>(),  container.Inject<Program>(),
                                     container.Inject<Cycle>(),  container.Inject<SoundManager>(),
                                     container.Inject<Screen>(), project };
                });
        container.BindUnique<application>(
                [&]
                {
                    return application{ container.Inject<Screen>(),       container.Inject<RenderManager>(),
                                        container.Inject<SoundManager>(), container.Inject<Timeline>(),
                                        container.Inject<Timer>(),        container.Inject<Program>() };
                });

        /* TODO replace manual functor resolution with in-place factories. Examples follow:
           container.BindUniqueFromFactory<Cycle, Cycle, Program, Timer, InputManager, RenderManager>();
           container.BindSharingFromFactory<Timeline, Timeline, Timer, Cycle, SoundManager, Screen>();
           */
    }

}
