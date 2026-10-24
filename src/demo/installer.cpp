module demo;

import engine;

namespace MoleDemo
{
    using namespace mole_def;

    void InstallBindings(Container& container, std::string& project)
    {
        container.BindShared<Timer>();
        container.BindShared<SoundManager>();
        container.BindShared<Screen>([] { return Screen{ 600, 300 }; }); // TO DO get from config
        container.BindShared<Program>([&] { return Program{ container.Inject<Screen>() }; });
        container.BindShared<SDL::SDLManager>();
        container.BindShared<RenderManager, RenderManager, Screen, SDL::SDLManager>();
        container.BindShared<InputManager, InputManager, SDL::SDLManager>();
        container.BindShared<Cycle, Cycle, Program, Timer, InputManager, RenderManager>();
        container.BindShared<Timeline, Timeline, Timer, Program, Cycle, SoundManager, Screen>();
        container.BindUnique<application, application, Screen, RenderManager, SoundManager, Timeline, Timer, Program>();
    }
}
