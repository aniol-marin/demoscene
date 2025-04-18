export module demo;

import std;
import injection;
import definitions;
import program;
import input;
import timer;
import raudio;
import sound;
import render;
import timeline;
import cycle;

using Container = MoleDemo::Container;

namespace MoleDemo {

	export class Demo;
}

class MoleDemo::Demo
{
	RAudio::AudioManager am {};
	Screen screen {600, 300};
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

	void LoadData(std::string source) {}
	void LoadTimeline(std::string source) {	}
	void Load(std::string source)
	{
		for (Loadable* item : loadables) {
			item->Load(source);
		}
	}
	
	void Unload()
	{
		for (Loadable* item : loadables) {
			item->Unload();
		}
	}

	void Init()
	{
		InstallBindings();

		initializables.push_back(&container.Inject<RenderManager>());
		initializables.push_back(timeline);
		initializables.push_back(sound);

		loadables.push_back(timeline);
		loadables.push_back(sound);

		timer->SetFPS(60);

		for (Initializable* item : initializables) {
			item->Init();
		}

		Load(source);
	}


	void Finalize()
	{
		Unload();

		for (Initializable* item : initializables) {
			item->Finalize();
		}
	}

	void InstallBindings()
	{
		container.BindShared<Timer>();
		container.BindShared<SoundManager>();
		container.BindShared<InputManager>();
		container.BindShared<Screen>([this]{ return Screen{this->screen}; });
		container.BindShared<Program>([&]{ return Program{ container.Inject<Screen>() }; });
		container.BindShared<RenderManager>([&]{ return RenderManager{ container.Inject<Screen>() }; });
		container.BindShared<Cycle>( [&] { return Cycle
		{
			container.Inject<Program>(),
			container.Inject<Timer>(),
			container.Inject<InputManager>(),
			container.Inject<RenderManager>()
		};});
		container.BindShared<Timeline>( [&] { return Timeline
		{
			container.Inject<Timer>(),
			container.Inject<Program>(),
			container.Inject<Cycle>(),
			container.Inject<SoundManager>(),
			container.Inject<Screen>()
		};});

		/* TODO replace manual functor resolution with in-place factories. Examples follow:
		container.BindUniqueFromFactory<Cycle, Cycle, Program, Timer, InputManager, RenderManager>();
		container.BindSharingFromFactory<Timeline, Timeline, Timer, Cycle, SoundManager, Screen>();
		*/
		//
		//Self injection (TO DO separate concerns)
		program = &container.Inject<Program>();
		timer = &container.Inject<Timer>();
		sound = &container.Inject<SoundManager>();
		timeline = &container.Inject<Timeline>();

	}

public:
	Demo(std::string project) :
		project {project},
		container {}
	{
	}

	void Run()
	{
		Init();
		sound->Play();
		timeline->Start();

		while (program->Running()) {
			sound->Update();
			timeline->Update();
		}

		sound->Stop();
		Finalize();
	}
};

