module;

#include <iostream>
#include <string>
#include <typeinfo>

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

        Finalize();
    }

    void Demo::Init(std::string& project)
    {
        InstallBindings(container, project);

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
}
