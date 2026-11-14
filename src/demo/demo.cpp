module demo;

import engine;
import std;

namespace MoleDemo
{
    using namespace mole_def;

    void Demo::Run()
    {
        Init();

        container.Inject<application>().run();

        Finalize();
    }

    void Demo::Init()
    {
        std::string project{};
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
