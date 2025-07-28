import std;
import engine;
import injection;
import definitions;
import program;
import input;
import timer;
import sound;
import render;
import timeline;
import cycle;
import effect;
import stars;
// leaked implementation
import raudio;
import sdl;

using namespace MoleDemo;
using Container = MoleDemo::Container;

void InstallBindings(Container& container);

int main()
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
    timer.SetEndTime(15);
    renderable.Load();

    while (program.Running() && !timer.EndReached())
    {
        delta = timer.GetDeltaTime();
        renderable.Update(intensity, delta);

        sdl.LockSurface();
        index i{ 0 };
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

void InstallBindings(Container& container)
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
    container.BindShared<Cycle>(
            [&]
            {
                return Cycle{ container.Inject<Program>(),
                              container.Inject<Timer>(),
                              container.Inject<InputManager>(),
                              container.Inject<RenderManager>() };
            });
}
