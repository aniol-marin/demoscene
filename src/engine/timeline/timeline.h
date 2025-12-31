#ifndef MOLE_TIMELINE_H
#define MOLE_TIMELINE_H

#include "Effect.h"
#include "cycle.h"
#include "definitions.h"
#include "effects.h"
#include "program.h"
#include "render.h"
#include "renderables.h"
#include "sound.h"
#include "timer.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using namespace mole_def;

namespace MoleDemo
{
    typedef Transition* TransitionHandle;
    typedef bool (*end_callback)();
    struct Event;

    struct Events : std::queue<Event*>
    {
    };
    struct EffectsRepository : std::vector<Effect*>
    {
    };
    struct LayersRepository : std::vector<Layer*>
    {
    };
}

namespace MoleDemo
{
    struct Event
    {
        const Timestamp time;
        Renderable* const background;
        Renderable* const foreground;

        Event(Timestamp time, Renderables renderables);
        Event(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transitionType);
        ~Event() {}

        bool TriggerReached(seconds current);
        bool Done(milliseconds deltaTime);
        void Update(permille intensity, permille deltaTime);
        Renderables GetRenderables();

    private:
        end_callback isDone;
        bool instantaneous;
        Renderables renderables;
        TransitionHandle transition;
        void UpdateLayers(permille i, permille d);
        void UpdateTransition(permille i, permille d);
    };

    class Timeline
      : public Initializable
      , public Loadable
    {
        SoundManager& sound;
        Screen& screen;
        Timer& timer;
        Program& program;
        Cycle& cycle;
        LayersRepository availableLayers;
        EffectsRepository availableEffects;
        Renderables renderables;
        Events events;
        Event* currentEvent;
        const std::string& project;
        bool initialized;
        bool loaded;
        bool started;

        void UpdateRenderables(Renderables newLayers); // TO DO simplify
        void HandleTimeline(); // TO DO simplify

        template<typename T>
        T* CreateEffect() // TO DO encapsulate
        {
            T* effect(new T(&timer, &screen));
            availableEffects.push_back(effect);
            return effect;
        }

        Layer* CreateLayer(BlendMode mode, Effect* effect); // TO DO encapsulate

        Event* CreateEvent(Timestamp time, Renderables renderables);
        Event* CreateEvent(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transition);

        void LoadInternal(const std::string& content); // TO DO simplify
    public: // TO DO refactor
        void Init(); // TO DO simplify
        void Finalize(); // TO DO simplify
        void Load(const std::string& content);
        void Unload(); // TO DO simplify
    public:
        Timeline(Timer& timer,
                 Program& program,
                 Cycle& cycle,
                 SoundManager& sound,
                 Screen& screen,
                 const std::string& project);
        ~Timeline() {}

        void Start();
        void Update();
        void Stop();
    };
}
#endif
