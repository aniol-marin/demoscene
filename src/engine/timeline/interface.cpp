export module timeline;

import std;
import definitions;
import effect;
/* TODO move to implementation
import effects;
 */
import renderables;
import timer;
import cycle;
import sound;
/* TODO move to implementation
import raudio;
 */
import program;
import render;

namespace MoleDemo
{
    using namespace mole_def;

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
    using namespace mole_def;

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
        /*
        SoundManager& sound;
         */
        Screen& screen;
        Timer& timer;
        Program& program;
        Cycle& cycle;
        LayersRepository availableLayers;
        EffectsRepository availableEffects;
        Renderables renderables;
        Events events;
        Event* currentEvent;
        void UpdateRenderables(Renderables newLayers);
        void HandleTimeline();

        template<typename T>
        T* CreateEffect()
        {
            std::unique_ptr<T> p_effect{ std::make_unique<T>(&timer, &screen) };
            T* effect{ p_effect.get() };
            availableEffects.push_back(std::move(p_effect));
            return effect;
        }

        Layer* CreateLayer(BlendMode mode, Effect* effect);

        std::unique_ptr<Event> CreateEvent(Timestamp time, Renderables renderables);
        std::unique_ptr<Event> CreateEvent(Timestamp time,
                                           Renderable* background,
                                           Renderable* foreground,
                                           TransitionType transition);

    public:
        Timeline(Timer& timer, Program& program, Cycle& cycle /*, SoundManager& sound*/, Screen& screen);

        void Init();
        void Load(std::string content);
        void Start();
    };
}
