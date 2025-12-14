#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <type_traits>

import timeline;
// dependencies:
import cycle;
import definitions;
import input;
import program;
import render;
import sdl_wrapper;
import sound;
import timer;

SCENARIO("Timeline")
{
	GIVEN("a timeline")
	{
		WHEN("first and foremost")
		{
			THEN("unit tests should run")
			{
				CHECK(true);
			}
			THEN("shouldn't be copyable")
			{
				CHECK(std::is_copy_constructible_v<MoleDemo::Timeline> == false);
			}
			THEN("its dependencies should work")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					MoleDemo::Timer _ {};
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					mole_def::Screen _ {1, 1};
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					mole_def::Screen screen {1, 1};
					MoleDemo::Program _ { screen };
				}));
				// ...
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					MoleDemo::Timer timer {};
					mole_def::Screen screen {1, 1};
					MoleDemo::Program program { screen };
					SDL::SDLManager sdl_manager { };
					MoleDemo::InputManager input_manager { sdl_manager };
					MoleDemo::RenderManager render_manager { screen, sdl_manager };

					MoleDemo::Cycle _ { program, timer, input_manager, render_manager };
				}));
				// ...
			}
		}
		AND_WHEN("properly instantiated")
		{
			THEN("the instantiation cycle must not throw")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					MoleDemo::Timer timer {};
					mole_def::Screen screen {1, 1};
					MoleDemo::Program program { screen };
					SDL::SDLManager sdl_manager { };
					MoleDemo::InputManager input_manager { sdl_manager };
					MoleDemo::RenderManager render_manager { screen, sdl_manager };
					MoleDemo::Cycle cycle { program, timer, input_manager, render_manager };
					MoleDemo::SoundManager sound_manager { };

					MoleDemo::Timeline _ {
						timer,
						program,
						cycle,
						sound_manager,
						screen,
						"test project"
					};
				}));
			}
		}
		AND_WHEN("properly used")
		{
			MoleDemo::Timer timer {};
			mole_def::Screen screen {1, 1};
			MoleDemo::Program program { screen };
			SDL::SDLManager sdl_manager { };
			MoleDemo::InputManager input_manager { sdl_manager };
			MoleDemo::RenderManager render_manager { screen, sdl_manager };
			MoleDemo::Cycle cycle { program, timer, input_manager, render_manager };
			MoleDemo::SoundManager sound_manager { };

			MoleDemo::Timeline timeline {
				timer,
				program,
				cycle,
				sound_manager,
				screen,
				"test project"
			};

			THEN("it should work as an Initializable")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					timeline.Init();
					timeline.Finalize();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Init();
					timeline.Init();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Finalize();
					timeline.Finalize();
				}));
			}
			THEN("it should work as a Loadable")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					timeline.Init();
					timeline.Load("unused string");
					timeline.Unload();
					timeline.Finalize();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Init();
					timeline.Load("unused string");
					timeline.Load("unused string");
					timeline.Finalize();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Init();
					timeline.Unload();
					timeline.Unload();
					timeline.Finalize();
				}));
			}
			THEN("it should be able to start")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					timeline.Init();
					timeline.Load("unused string");
					timeline.Start();
					timeline.Stop();
					timeline.Unload();
					timeline.Finalize();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Init();
					timeline.Load("unused string");
					timeline.Start();
					timeline.Start();
					timeline.Stop();
					timeline.Unload();
					timeline.Finalize();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Init();
					timeline.Load("unused string");
					timeline.Start();
					timeline.Stop();
					timeline.Stop();
					timeline.Unload();
					timeline.Finalize();
				}));
				REQUIRE_THROWS( std::invoke([&]()
				{
					timeline.Init();
					timeline.Start();
					timeline.Stop();
					timeline.Unload();
					timeline.Finalize();
				}));
			}
		}
	}
}
