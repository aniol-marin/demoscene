#include <iostream>
#include <string>
#include <typeinfo>
#include "demo.h"

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
