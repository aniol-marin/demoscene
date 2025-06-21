#ifndef MOLE_DEMO_H
#define MOLE_DEMO_H

#include <string>
#include <vector>
#include <map>

#include "definitions.h"
#include "injection.h"
#include "program.h"
#include "sound.h"
#include "timer.h"
#include "timeline.h"

namespace MoleDemo
{
    using namespace mole_def;
    using Container = MoleDemo::Container;

    class Demo
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

    class MoleDemo::RenderManager : public Initializable
    {
    public:
        RenderManager() = delete;
        RenderManager(Screen& screen, SDL::SDLManager& sdl);
        RenderManager(const RenderManager&) = default;
        RenderManager(RenderManager&&) = default;
        ~RenderManager() = default;

    private:
        const Screen m_screen;
        RenderQueue* queue;
        PixelBuffer buffer;
        StencilBuffer mask;
        SDL::SDLManager& sdl;

        void Lock();
        void Unlock();
        void Render();

    public:
        void Init();
        void Finalize();
        void Draw(Renderables& renderables);
        StencilBuffer& GetMask();
    };
}

#endif
