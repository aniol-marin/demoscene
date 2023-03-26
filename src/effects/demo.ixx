export module demo;

import definitions;
import injection;
import timeline;
import program;
import input;
import interfaces;
import render;
import cycle;
import timer;
import sound;
import <string>;
import <vector>;
import <thread>;

namespace MoleDemo {


	export class Demo :
		public Initializable,
		Loadable {
		std::string source;
		std::vector<Initializable*> initializables;
		std::vector<Loadable*> loadables;
		RenderManager* render;
		SoundManager* sound;
		Timeline* timeline;
		Timer* timer;
		Program* program;
		// TODO multithread
		std::thread mainThread;
		std::thread musicThread;
		std::thread loadingThread;
		void LoadData(std::string source) {}
		void LoadTimeline(std::string source) {	}
		void InstallBindings() {
			Container container{};

			container.BindShared<Screen, Screen>();
			container.BindShared<Timer, Timer>();
			container.BindShared<SoundManager, SoundManager>();
			container.BindShared<InputManager, InputManager>();

			// TODO replace default constructor with parametrized injection and/or binding
			// TODO replace manual resolution with Factories. Examples follow:
			/*
			container.BindSharingFactory<Program, Program, Screen>();
			container.BindSharingFactory<RenderManager, RenderManager, Screen>();
			container.BindUniqueFactory<Cycle, Cycle, Program, Timer, RenderManager>();
			container.BindSharingFactory<Timeline, Timeline, Timer, Cycle>();
			*/
			InputManager* input = container.Inject<InputManager>();
			timer = container.Inject<Timer>();
			sound = container.Inject<SoundManager>();
			program = new Program(
				container.Inject<Screen>());
			render = new RenderManager(
				container.Inject<Screen>());
			Cycle* cycle = new Cycle(
				program,
				container.Inject<Timer>(),
				container.Inject<InputManager>(),
				render);
			timeline = new Timeline(
				container.Inject<Timer>(),
				program,
				cycle,
				container.Inject<SoundManager>(),
				container.Inject<Screen>());

			initializables.push_back(render);
			initializables.push_back(timeline);
			initializables.push_back(sound);

			loadables.push_back(timeline);
			loadables.push_back(sound);
		}
		void Load(std::string source) {
			for (Loadable* item : loadables) {
				item->Load(source);
			}
		}
		void Unload() {
			for (Loadable* item : loadables) {
				item->Unload();
			}
		}
	public:
		Demo(std::string project) :
			source{ project },
			Initializable{},
			Loadable() {}
		void Init() {

			InstallBindings();

			timer->SetFPS(60);

			for (Initializable* item : initializables) {
				item->Init();
			}

			Load(source);
		}
		void Run() {
			// TODO create and manage separate threads
			sound->Play();
			timeline->Start();

			while (program->Running()) {
				sound->Update();
				timeline->Update();
			}
		}
		void Finalize() {

			Unload();

			for (Initializable* item : initializables) {
				item->Finalize();
			}
		}
	};
}