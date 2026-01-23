module;

#include <functional>
#include <memory>
#include <queue>
#include <string_view>
#include <vector>

export module timeline;

import cycle;
import effect;
import program;
import renderables;
import sound;

using namespace mole_def;

namespace MoleDemo
{
    export class Timeline;

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
        std::string_view project;
        bool initialized{ false };
        bool loaded{ false };
        bool started{ false };

        void UpdateRenderables(Renderables newLayers); // TO DO simplify
        void HandleTimeline(); // TO DO simplify

        template<typename T>
        T* CreateEffect() // TO DO encapsulate
        {
            std::unique_ptr<T> p_effect{ std::make_unique<T>(&timer, &screen) };
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

        void LoadInternal(std::string_view content); // TO DO simplify
    public: // TO DO refactor
        void Init() override; // TO DO simplify
        void Finalize() override; // TO DO simplify
        void Load(std::string_view content) override;
        void Unload() override; // TO DO simplify
    public:
        Timeline() = delete;
        Timeline(Timer& timer,
                 Program& program,
                 Cycle& cycle,
                 SoundManager& sound,
                 Screen& screen,
                 std::string_view project);
        Timeline(const Timeline&) = delete;
        Timeline(Timeline&&) = default;
        ~Timeline() = default;

        void Start();
        void Update();
        void Stop();
    };
}
