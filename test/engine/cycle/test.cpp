#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <functional>
#include <iostream>

import cycle;
// dependencies:
import cycle;
import definitions;
import input;
import program;
import render;
import sdl_wrapper;
import timer;

SCENARIO("Cycle")
{
	GIVEN("a cycle")
	{
		WHEN("properly instantiated")
		{
			THEN("unit tests should run")
			{
				CHECK(true);
			}
			THEN("shouldn't be copyable")
			{
				CHECK(std::is_copy_constructible_v<MoleDemo::Cycle> == false);
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
				//...
			}
			THEN("it must not throw")
			{
				MoleDemo::Timer timer {};
				mole_def::Screen screen {1, 1};
				MoleDemo::Program program { screen };
				SDL::SDLManager sdl_manager { };
				MoleDemo::InputManager input_manager { sdl_manager };
				MoleDemo::RenderManager render_manager { screen, sdl_manager };

				REQUIRE_NOTHROW(MoleDemo::Cycle { program, timer, input_manager, render_manager });
			}
		}
	}
}
