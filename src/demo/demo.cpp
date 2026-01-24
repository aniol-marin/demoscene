#include "demo.h"

#include <string>

namespace
{
    using namespace mole_def;
    using namespace MoleDemo;

    static Container container = Container();
    static Screen screen = Screen(0, 0);
    static std::string project = std::string();
}

namespace MoleDemo
{
    using namespace mole_def;

    Demo::Demo(std::string a_project) : container()
    {
        // TO DO load values from config string
    }

    void Demo::Run()
    {
        std::string project; // TO DO get values from constructor maybe
        Init(project);

        container.Inject<application>().run();

        Finalize();
    }

    void Demo::Init(std::string& project)
    {
        InstallBindings(container, project);

        // TO DO automatic interface detection
        initializables.push_back(&container.Inject<RenderManager>());
        initializables.push_back(&container.Inject<SoundManager>());
        initializables.push_back(&container.Inject<Timeline>());

        if (!initializables.empty())
            for (Initializable* item: initializables)
            {
                for (std::vector<Initializable*>::iterator item = initializables.begin(); item != initializables.end();
                     ++item)
                {
                    (*item)->Init();
                }
            }

        loadables.push_back(&container.Inject<Timeline>());
        loadables.push_back(&container.Inject<SoundManager>());
        if (!loadables.empty())
            for (std::vector<Loadable*>::iterator item = loadables.begin(); item != loadables.end(); ++item)
            {
                (*item)->Load(project);
            }
    }

    void Demo::Finalize()
    {
        if (!loadables.empty())
            for (Loadable* item: loadables)
                for (std::vector<Loadable*>::iterator item = loadables.begin(); item != loadables.end(); ++item)
                {
                    (*item)->Unload();
                }
        if (!initializables.empty())
            for (std::vector<Initializable*>::iterator item = initializables.begin(); item != initializables.end();
                 ++item)
            {
                (*item)->Finalize();
            }
    }
}
