#ifndef MOLE_DEMO_H
#define MOLE_DEMO_H

#include <string>
#include <vector>
#include "engine.h"

using namespace mole_def;

namespace MoleDemo
{
    class Demo
    {
        std::string source;
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
}

#endif
