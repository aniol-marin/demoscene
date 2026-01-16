export module demo;

import std;
import engine;

using namespace mole_def;

namespace MoleDemo
{
    export class Demo;
    class application;
}

namespace MoleDemo
{
    class Demo
    {
        Container container;
        std::vector<Initializable*> initializables{};
        std::vector<Loadable*> loadables{};

        void Init(std::string& project);
        void Finalize();
        void InstallBindings(std::string& project);

    public:
        Demo(std::string project);
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
