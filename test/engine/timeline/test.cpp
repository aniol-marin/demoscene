#include <catch2/catch_test_macros.hpp>

import std;
import timeline;
// dependencies:
import cycle;
import definitions;
import input;
import program;
import render;
import sdl_wrapper;
import timer;

SCENARIO("Timeline")
{
	GIVEN("a timeline")
	{
		WHEN("properly instantiated")
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
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					MoleDemo::Timer timer {};
					mole_def::Screen screen {1, 1};
					MoleDemo::Program program { screen };
					SDL::SDLManager sdl_manager { };
					MoleDemo::InputManager input_manager { sdl_manager };
					MoleDemo::RenderManager render_manager { screen, sdl_manager };
					MoleDemo::Cycle cycle { program, timer, input_manager, render_manager };

					//MoleDemo::SoundManager sound_manager { ...};
					MoleDemo::Timeline _ {
						timer,
						program,
						cycle,
						screen,
						"test project"
					};
					/*
					*/
						/*sound_manager,*/
				}));
				CHECK(true);
			}
			AND_THEN("it must not throw")
			{
				CHECK(true);
			}
			AND_THEN("more unit tests should be written")
			{
				CHECK(false);
			}
		}
	}
}
