export module demo;

using Container = MoleDemo::Container;

namespace MoleDemo

    export class Demo;
}

class MoleDemo::Demo
{
    RAudio::AudioManager am{};
    Screen screen{ 600, 300 };
    const std::string project{};
    std::string source{};
    Container container;
    std::vector<Initializable*> initializables;
    std::vector<Loadable*> loadables;
    RenderManager* render;
    SoundManager* sound;
    Timeline* timeline;
    Timer* timer;
    Program* program;

    void LoadData(std::string source);
    void LoadTimeline(std::string source);
    void Load(std::string source);
    void Unload();
    void Init();
    void Finalize();
    void InstallBindings();

public:
    Demo(std::string project);
    void Run();
};
