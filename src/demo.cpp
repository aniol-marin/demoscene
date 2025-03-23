module;

#include <string>
#include <any> //needed due to injection for some reason
#include <iostream>
//#include <thread>

export module demo;

import injection;
import definitions;
import program;
import input;
import timer;
import sound;
import render;
import timeline;
import cycle;
 /*
 import <string>;
 import <vector>;
 import <thread>;
 */

using Container = MoleDemo::Container;

namespace MoleDemo {

	export class Demo;
}

class MoleDemo::Demo
{
	Screen screen {600, 300};
	const std::string project;
	Container container;

	void Init()
	{
		std::cout << "[MOCK] Initializing..." << std::endl;
		InstallBindings();


		//Self injection
		/*
		program = container.Inject<Program>();
		timer = container.Inject<Timer>();
		sound = container.Inject<SoundManager>();
		timeline = container.Inject<Timeline>();

		initializables.push_back(container.Inject<RenderManager>());
		initializables.push_back(timeline);
		initializables.push_back(sound);

		loadables.push_back(timeline);
		loadables.push_back(sound);
		*/
	}


	void Finalize()
	{
		std::cout << "[MOCK] Finalizing" << std::endl;
	}

	void InstallBindings()
	{
		std::cout << "[MOCK] Installing bindings.." << std::endl;
		
		container.BindShared<Timer>();
		container.BindShared<SoundManager>();
		container.BindShared<InputManager>();
		container.BindShared<Screen>([]{ return Screen{600, 480}; });
		container.BindShared<Program>([&]{ return Program{ container.Inject<Screen>() }; });
		container.BindShared<RenderManager>([&]{ return RenderManager{ container.Inject<Screen>() }; });
		container.BindShared<Cycle>(
			[&]
			{
				return Cycle{
					container.Inject<Program>(),
					container.Inject<Timer>(),
					container.Inject<InputManager>(),
					container.Inject<RenderManager>()
				};
			}
		);
		container.BindShared<Timeline>(
			[&]
			{
				return Timeline{
					container.Inject<Timer>(),
					container.Inject<Program>(),
					container.Inject<Cycle>(),
					container.Inject<SoundManager>(),
					container.Inject<Screen>()
				};
			}
		);

		/*
		// TODO replace default constructor with parametrized injection and/or binding
		// TODO replace manual resolution with Factories. Examples follow:
		 container.BindUniqueFactory<Cycle, Cycle, Program, Timer, RenderManager>();
		 container.BindSharingFactory<Timeline, Timeline, Timer, Cycle>();
		 */
	}

public:
	Demo(std::string project) :
		project {project},
		container {}
	{
		std::cout << "[MOCK] Loading project: " << project << std::endl;
	}

	void Run()
	{
		Init();
		std::cout << "[MOCK] Running..." << std::endl;
		Finalize();
	}
};

/*
class MoleDemo::Demo :
	public Initializable,
	Loadable {
		std::string source;
		Container container;
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
			container{},
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

			sound->Stop();
		}
		void Finalize() {

			Unload();

			for (Initializable* item : initializables) {
				item->Finalize();
			}
		}
};
*/
