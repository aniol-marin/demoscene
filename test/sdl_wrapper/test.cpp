#include<catch2/catch_test_macros.hpp>

#include <any> //needed due to injection for some reason
#include <functional>
#include <iostream>


import sdl; 

TEST_CASE("Project is set up properly", "[SDL Wrapper]")
{
	SECTION("test target works")
	{
		REQUIRE(true);
	}
}

TEST_CASE("Manager basic behavior", "[SDL Wrapper]")
{
	SECTION("Manager can be instantiated")
	{
		REQUIRE(true);
		REQUIRE_NOTHROW(SDL::SDLManager{});
	}

	SECTION("SDL can be started and stopped")
	{
		SDL::SDLManager m {};

		REQUIRE_NOTHROW(m.Init({640, 480}));
		REQUIRE_NOTHROW(m.Finalize());
	}
}

