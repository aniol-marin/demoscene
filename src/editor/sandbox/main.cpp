#include <string>
#include <iostream>
#include <typeinfo>

import engine;
import stars;

using namespace MoleDemo;
using namespace mole_def;
using Container = MoleDemo::Container;

void
InstallBindings(Container& container);

int
main(int argc, char** argv)
{
    Container container;
    InstallBindings(container);

    Program& program{ container.Inject<Program>() };
    Timer& timer{ container.Inject<Timer>() };
    Screen& screen{ container.Inject<Screen>() };
    SDL::SDLManager& sdl{ container.Inject<SDL::SDLManager>() };

    const permille intensity{ 500 };
    milliseconds delta{};
    Stars stars{ &timer, &screen };
    Effect& renderable{ stars };

    sdl.Init(screen);
    timer.SetFPS(60);

    int requested_timeout{};
    std::istringstream s{ argv[1] };
    s >> requested_timeout;
    int timeout{ requested_timeout ? requested_timeout : 15 };
    std::cout << "\n set timeout to: [" << timeout << "]\n";
    timer.SetEndTime(timeout);
    renderable.Load();

    while (program.Running() && !timer.EndReached())
    {
        delta = timer.GetDeltaTime();
        renderable.Update(intensity, delta);

        sdl.LockSurface();
        index_t i{ 0 };
        for (point1D y{ 0 }; y < screen.h; ++y)
        {
            for (point1D x{ 0 }; x < screen.w; ++x)
            {
                sdl.PutPixel(x, y, renderable.GetPixel(i));
                ++i;
            }
        }
        sdl.UpdateSurface();
        sdl.UnlockSurface();

        timer.WaitUntilNextFrame();
    }

    std::cout << std::endl;

    renderable.Unload();
    sdl.Finalize();

    return 0;
}

void
InstallBindings(Container& container)
{
    container.BindShared<Timer>();
    container.BindShared<Screen>([] { return Screen{ 640, 480 }; });
    container.BindShared<SDL::SDLManager>();
    container.BindShared<RenderManager>( //
            [&] //
            { //
                return RenderManager{ container.Inject<Screen>(), container.Inject<SDL::SDLManager>() }; //
            });
    container.BindShared<InputManager>([&] { return InputManager{ container.Inject<SDL::SDLManager>() }; });
    container.BindShared<Program>([&] { return Program{ container.Inject<Screen>() }; });
    container.BindShared<Cycle>( //
            [&] //
            {
                return Cycle{ container.Inject<Program>(),
                              container.Inject<Timer>(),
                              container.Inject<InputManager>(),
                              container.Inject<RenderManager>() };
            });
}
