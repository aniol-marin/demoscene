export module demo;

import std;
import engine;

using namespace mole_def;

namespace MoleDemo
{
    export class Demo;
    class application;
    void InstallBindings(Container& container, std::string& project);
}

namespace MoleDemo
{
    class Demo
    {
        Container container;
        std::vector<Initializable*> initializables{};
        std::vector<Loadable*> loadables{};

        void Init();
        void Finalize();

    public:
        Demo() = default;

        void Run();
    };

    class application
    {
        Screen& screen;
        RenderManager& render;
        SoundManager& sound;
        Timeline& timeline;
        Timer& timer;
        Program& program;

    public:
        explicit application(Screen& screen,
                             RenderManager& render,
                             SoundManager& sound,
                             Timeline& timeline,
                             Timer& timer,
                             Program& program);

        void run();
    };
}
