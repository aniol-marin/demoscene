module demo;

using Container = MoleDemo::Container;

namespace MoleDemo
{
    void Demo::LoadData(std::string source) {}

    void Demo::LoadTimeline(std::string source) {}

    void Demo::Load(std::string source)
    {
        for (Loadable* item: loadables)
        {
            item->Load(source);
        }
    }

    void Demo::Unload()
    {
        for (Loadable* item: loadables)
        {
            item->Unload();
        }
    }

    void Demo::Init()
    {
        InstallBindings();

        initializables.push_back(&container.Inject<RenderManager>());
        initializables.push_back(timeline);
        initializables.push_back(sound);

        loadables.push_back(timeline);
        loadables.push_back(sound);

        timer->SetFPS(60);

        for (Initializable* item: initializables)
        {
            item->Init();
        }

        Load(source);
    }

    void Demo::Finalize()
    {
        Unload();

        for (Initializable* item: initializables)
        {
            item->Finalize();
        }
    }

    void Demo::InstallBindings()
    {
        container.BindShared<Timer>();
        container.BindShared<SoundManager>();
        container.BindShared<Screen>([this] { return Screen{ this->screen }; });
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

        /* TODO replace manual functor resolution with in-place factories. Examples follow:
        container.BindUniqueFromFactory<Cycle, Cycle, Program, Timer, InputManager, RenderManager>();
        container.BindSharingFromFactory<Timeline, Timeline, Timer, Cycle, SoundManager, Screen>();
        */
        //
        // Self injection (TO DO separate concerns)
        program = &container.Inject<Program>();
        timer = &container.Inject<Timer>();
        sound = &container.Inject<SoundManager>();
        timeline = &container.Inject<Timeline>();
    }

    Demo::Demo(std::string project) : project{ project }, container{} {}

    void Demo::Run()
    {
        Init();
        sound->Play();
        timeline->Start();

        while (program->Running())
        {
            sound->Update();
            timeline->Update();
        }

        sound->Stop();
        Finalize();
    }
}
