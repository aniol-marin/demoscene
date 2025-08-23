export module timeline;

import std;
import cycle;
import definitions;
import effect;
import effects; //TODO encapsulate serialization in factory
import program;
import raudio;
import render;
import renderables;
import serialization;
import sound;
import timer;

namespace MoleDemo
{
	export class Timeline;
}

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
} // namespace MoleDemo

struct MoleDemo::Event
{
	const Timestamp time;
	Renderable* const background;
	Renderable* const foreground;
	Event(Timestamp time, Renderables renderables);
	Event(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transitionType);
	~Event() = default;

	bool TriggerReached(seconds current);{ return current >= time.start; }
	bool Done(milliseconds deltaTime);{ return isDone(); }
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

class MoleDemo::Timeline
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
	std::string project;
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
	Solid* CreateSolid(const pugi::xml_node node);

	public:
	Timeline(Timer& timer, Program& program, Cycle& cycle, SoundManager& sound, Screen& screen, std::string_view project);

	void Init();
	void Load(std::string content);
	void Start();
	void Update();
	void Unload();
	void Finalize();
};

