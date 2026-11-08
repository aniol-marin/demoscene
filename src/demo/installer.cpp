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
        container.BindShared<SoundManager>([&] { return new SoundManager{ container.Inject<SDL::SDLManager>() }; });
        container.BindShared<Screen>([] { return new Screen{ 600, 300 }; }); // TO DO get from config
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
                    return new Timeline{ container.Inject<Timer>(),
                                         container.Inject<Program>(),
                                         container.Inject<Cycle>(),
                                         container.Inject<SoundManager>(),
                                         container.Inject<Screen>() };
                });
        container.BindUnique<application>(
                [&]
                {
                    return new application{ container.Inject<Screen>(),       container.Inject<RenderManager>(),
                                            container.Inject<SoundManager>(), container.Inject<Timeline>(),
                                            container.Inject<Timer>(),        container.Inject<Program>() };
                });
    }
}
