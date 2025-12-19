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
    struct Event;
    struct Events : std::queue<std::unique_ptr<Event>>
    {
    };
    struct EffectsRepository : std::vector<std::unique_ptr<Effect>>
    {
    };
    struct LayersRepository : std::vector<std::unique_ptr<Layer>>
    {
    };

    using TransitionHandle = std::unique_ptr<Transition>;
}

namespace MoleDemo
{
    struct Event
    {
        const Timestamp time;
        Renderable* const background;
        Renderable* const foreground;

        Event() = delete;
        Event(Timestamp time, Renderables renderables);
        Event(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transitionType);
        ~Event() = default;

        bool TriggerReached(seconds current);
        bool Done(milliseconds deltaTime);
        void Update(permille intensity, permille deltaTime);
        Renderables GetRenderables();

    private:
        std::function<bool()> isDone;
        bool instantaneous;
        Renderables renderables;
        TransitionHandle transition;
        milliseconds timeSinceStart;
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
        bool initialized{ false };
        bool loaded{ false };
        bool started{ false };

        void UpdateRenderables(Renderables newLayers); // TO DO simplify
        void HandleTimeline(); // TO DO simplify

        template<typename T>
        T* CreateEffect() // TO DO encapsulate
        {
            std::unique_ptr<T> p_effect{ new T{ &timer, &screen } };
            T* effect{ p_effect.get() };
            availableEffects.push_back(std::move(p_effect));
            return effect;
        }

        Layer* CreateLayer(BlendMode mode, Effect* effect); // TO DO encapsulate

        std::unique_ptr<Event> CreateEvent(Timestamp time, Renderables renderables);
        std::unique_ptr<Event> CreateEvent(Timestamp time,
                                           Renderable* background,
                                           Renderable* foreground,
                                           TransitionType transition);

        void LoadInternal(const std::string& content); // TO DO simplify
    public: // TO DO refactor
        void Init() override; // TO DO simplify
        void Finalize() override; // TO DO simplify
        void Load(const std::string& content) override;
        void Unload() override; // TO DO simplify
    public:
        Timeline() = delete;
        Timeline(Timer& timer,
                 Program& program,
                 Cycle& cycle,
                 SoundManager& sound,
                 Screen& screen,
                 const std::string& project);
        Timeline(const Timeline&) = delete;
        Timeline(Timeline&&) = default;
        ~Timeline() = default;

        void Start();
        void Update();
        void Stop();
    };
}
#endif
