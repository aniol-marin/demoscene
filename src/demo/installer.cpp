#include <iostream>
#include <string>
#include <typeinfo>
#include "demo.h"
#include "injection.h"

namespace
{
    MoleDemo::Container* g_container;
}

namespace MoleDemo
{
    using namespace mole_def;

    void* instantiate_timer()
    {
        return static_cast<void*>(new Timer());
    }

    void* instantiate_screen()
    {
        return static_cast<void*>(new mole_def::Screen(600, 300));
    }

    void* instantiate_program()
    {
        return static_cast<void*>(new Program(g_container->Inject<Screen>()));
    }

    void* instantiate_render_manager()
    {
        return static_cast<void*>(
                new RenderManager(g_container->Inject<Screen>(), g_container->Inject<SDL::SDLManager>()));
    }

    void* instantiate_input_manager()
    {
        return static_cast<void*>(new InputManager(g_container->Inject<SDL::SDLManager>()));
    }

    void* instantiate_cycle()
    {
        return static_cast<void*>(new Cycle(g_container->Inject<Program>(),
                                            g_container->Inject<Timer>(),
                                            g_container->Inject<InputManager>(),
                                            g_container->Inject<RenderManager>()));
    }

    void* instantiate_sound_manager()
    {
        return static_cast<void*>(new SoundManager());
    }

    void* instantiate_timeline()
    {
        std::string project;

        return static_cast<void*>(new Timeline(g_container->Inject<Timer>(),
                                               g_container->Inject<Program>(),
                                               g_container->Inject<Cycle>(),
                                               g_container->Inject<SoundManager>(),
                                               g_container->Inject<Screen>(),
                                               project));
    }

    void InstallBindings(Container& container, std::string& project)
    {
        g_container = &container;

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
    }
}
