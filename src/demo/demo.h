#ifndef MOLE_DEMO_H
#define MOLE_DEMO_H

#include <string>
#include <vector>
#include "engine.h"

using namespace mole_def;

namespace MoleDemo
{
    void InstallBindings(Container& container, std::string& project);

    class Demo
    {
        Container container;
        std::vector<Initializable*> initializables;
        std::vector<Loadable*> loadables;

        void Init(std::string& project);
        void Finalize();

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
#endif
