export module timeline;

import definitions;
import interfaces;
import effects;
import renderables;
import timer;
import cycle;
import sound;
import program;
import render;
import <string>;
import <queue>;
import <vector>;
import <memory>;
import <functional>;

namespace MoleDemo {

	export class Timeline;

	struct Event;
	struct Events : std::queue<std::unique_ptr<Event>> {};
	struct EffectsRepository : std::vector<std::unique_ptr<Effect>> {};
	struct LayersRepository : std::vector<std::unique_ptr<Layer>> {};

	using TransitionHandle = std::unique_ptr<Transition>;
}

struct MoleDemo::Event {
	const Timestamp time;
	Renderable* const background;
	Renderable* const foreground;
	Event(Timestamp time, Renderables renderables) :
		timeSinceStart{ 0 },
		time{ time },
		renderables{ renderables },
		background{  },
		foreground{  },
		isDone{ [] { return true; } },
		instantaneous{ true },
		transition{} {}
	Event(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transitionType) :
		timeSinceStart{ 0 },
		time{ time },
		renderables{ background, foreground },
		background{ background },
		foreground{ foreground },
		instantaneous{ false },
		isDone{ [&] { return timeSinceStart > this->time.duration; } },
		transition{} {

		switch (transitionType)
		{
		case TransitionType::Fade: {
			transition = std::make_unique<Fade>(time);
			transition->Bind(background, foreground);
			break;
		}
		default:
			transition = nullptr;
			break;
		}

	}
	~Event() {}

	bool TriggerReached(seconds current) {
		return current >= time.start;
	}
	bool Done(milliseconds deltaTime) {
		return isDone();
	}
	void Update(permille intensity, permille deltaTime) {
		timeSinceStart += deltaTime;
		if (instantaneous) {
			UpdateLayers(intensity, deltaTime);
		}
		else {
			transition->Update(intensity, deltaTime);
		}
	}
	Renderables GetRenderables() {
		Renderables active = Renderables{};
		if (!instantaneous) {

			if (!isDone()) {
				active.push_back(transition.get());
			}
			else {
				active.push_back(foreground);
			}
		}
		else {

			active = renderables;
		}
		return active;
	}
private:
	std::function<bool()> isDone;
	bool instantaneous;
	Renderables renderables;
	TransitionHandle transition;
	milliseconds timeSinceStart;
	void UpdateLayers(permille i, permille d) {
		for (Renderable* r : renderables) {
			r->Update(i, d);
		}
	}
	void UpdateTransition(permille i, permille d) {
		transition->Update(i, d);
	}
};

class MoleDemo::Timeline :
	public Initializable,
	public Loadable {
	SoundManager* const sound;
	Screen* const screen;
	Timer* const timer;
	Program* const program;
	Cycle* const cycle;
	LayersRepository availableLayers;
	EffectsRepository availableEffects;
	Renderables renderables;
	Events events;
	Event* currentEvent;
	void UpdateRenderables(Renderables newLayers) {

		Renderables* oldLayers = &renderables;

		// unload previously loaded effects (no longer needed)
		for (Renderable* oldLayer : *oldLayers) {
			Renderables::iterator unused = std::find(newLayers.begin(), newLayers.end(), oldLayer);
			if (unused != newLayers.end()) {
				//(*unused)->effect->Unload();
			}
		}

		// load previously unloaded effects
		for (Renderable* newLayer : newLayers) {
			Renderables::iterator unloaded = std::find(oldLayers->begin(), oldLayers->end(), newLayer);
			if (unloaded == oldLayers->end()) {
				//newLayer->effect->Load();
			}
		}

		renderables = newLayers;
		cycle->SetRenderables(renderables);
	}
	void HandleTimeline() {

		if (currentEvent != nullptr) {

			if (!currentEvent->Done(timer->GetDeltaTime())) {

				currentEvent->Update(sound->GetCurrentIntensity(), timer->GetDeltaTime());
			}
			else {

				UpdateRenderables(currentEvent->GetRenderables());
				currentEvent = nullptr;
				events.pop();
			}
		}
		else if (!events.empty() && events.front()->TriggerReached(timer->GetTime())) {

			currentEvent = events.front().get();
			UpdateRenderables(currentEvent->GetRenderables());
			cycle->SetRenderables(renderables);
		}
	}

	template <typename T>
	T* CreateEffect() {
		std::unique_ptr<T> p_effect{ std::make_unique<T>(timer, screen) };
		T* effect{ p_effect.get() };
		availableEffects.push_back(std::move(p_effect));
		return effect;
	}

	Layer* CreateLayer(BlendMode mode, Effect* effect) {
		std::unique_ptr<Layer> p_layer{ std::make_unique<Layer>(mode, effect) };
		Layer* layer{ p_layer.get() };
		availableLayers.push_back(std::move(p_layer));
		return layer;
	}

	std::unique_ptr<Event> CreateEvent(Timestamp time, Renderables renderables) {
		return std::move(std::make_unique<Event>(time, renderables));
	}

	std::unique_ptr<Event> CreateEvent(Timestamp time, Renderable* background, Renderable* foreground, TransitionType transition) {
		return std::move(std::make_unique<Event>(time, background, foreground, transition));
	}

public:
	Timeline(Timer* timer, Program* program, Cycle* cycle, SoundManager* sound, Screen* screen) :
		currentEvent{ nullptr },
		timer{ timer },
		program{ program },
		cycle{ cycle },
		sound{ sound },
		screen{ screen },
		renderables{} {}

	void Init() {
	}

	void Load(std::string content) {
		// TODO load project from JSON

		// TODO argument forwarding on CreateEffect template
		Solid* solid1{ CreateEffect<Solid>() };
		solid1->SetColor(black);

		Solid* solid2{ CreateEffect<Solid>() };
		solid2->SetColor(white);

		Gradient* gradient1{ CreateEffect<Gradient>() };
		gradient1->SetColors(white, black, black, white);

		Gradient* gradient2{ CreateEffect<Gradient>() };
		gradient2->SetColors(white, black, white, black);

		Gradient* gradient3{ CreateEffect<Gradient>() };
		gradient3->SetColors(white, red, green, blue);

		Gradient* gradient4{ CreateEffect<Gradient>() };
		gradient4->SetColors(black, tile, magenta, orange);

		// Layers
		Layer* stars{ CreateLayer(BlendMode::AlphaBlend, CreateEffect<Stars>()) };
		Layer* plasma{ CreateLayer(BlendMode::Override, CreateEffect<Plasma>()) };
		Layer* fire{ CreateLayer(BlendMode::AlphaBlend, CreateEffect<Fire>()) };
		Layer* black{ CreateLayer(BlendMode::Override, solid1) };
		Layer* white{ CreateLayer(BlendMode::Override, solid2) };
		Layer* verticalGradient{ CreateLayer(BlendMode::Override, gradient1) };
		Layer* diagonalGradient{ CreateLayer(BlendMode::Override, gradient2) };
		Layer* primaries{ CreateLayer(BlendMode::Override, gradient3) };
		Layer* secondaries{ CreateLayer(BlendMode::Override, gradient4) };

		// Layers initialization
		for (std::unique_ptr<Effect>& effect : availableEffects) {
			effect->Load();
		}

		// OK timeline
		renderables.push_back(black);
		events.push(std::make_unique<Event>(Timestamp{ 1, 2000 }, black, white, TransitionType::Fade));
		events.push(std::make_unique<Event>(Timestamp{ 3, 2000 }, white, verticalGradient, TransitionType::Fade));
		events.push(std::make_unique<Event>(Timestamp{ 5, 2000 }, verticalGradient, diagonalGradient, TransitionType::Fade));
		events.push(std::make_unique<Event>(Timestamp{ 7, 4000 }, diagonalGradient, primaries, TransitionType::Fade));
		events.push(std::make_unique<Event>(Timestamp{ 11, 512 }, primaries, secondaries, TransitionType::Fade));

		// Experimental
		events.push(std::make_unique<Event>(Timestamp{ 12, 0 }, Renderables{ stars, secondaries, stars }));
		events.push(std::make_unique<Event>(Timestamp{ 10, 0 }, Renderables{ plasma }));
		events.push(std::make_unique<Event>(Timestamp{ 12, 0 }, Renderables{ fire }));

		UpdateRenderables(renderables);
	}

	void Start() {
		timer->SetEndTime(sound->GetMusicDuration());
	}

	void Update() {

		HandleTimeline();

		cycle->PollEvents();
		cycle->Update(sound->GetCurrentIntensity());
		cycle->Draw();
		cycle->Synch();
	}

	void Unload() {
		for (std::unique_ptr<Effect>& effect : availableEffects) {
			effect->Unload();
		}
	}

	void Finalize() {}
};