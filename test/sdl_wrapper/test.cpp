#include<catch2/catch_test_macros.hpp>
#include <functional>
#include "sdl.h"

#include <any> //needed due to injection for some reason
#include <iostream>

/*
   import sdl; 
*/

TEST_CASE("Manager basic behavior", "[SDL Wrapper]")
{
	SECTION("Manager can be instantiated")
	{
		REQUIRE_NOTHROW(SDL::SDLManager{});
	}

	SECTION("SDL can be started and stopped")
	{
		SDL::SDLManager m {};

		REQUIRE_NOTHROW(m.Init({640, 480}));
		REQUIRE_NOTHROW(m.Finalize());
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.Finalize();
		}));
	}
}

TEST_CASE("Manager interface: surface interaction", "[SDL Wrapper]")
{
	SECTION("Surface can be locked and ulocked without restrictions")
	{
		SDL::SDLManager m {};

		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.Finalize();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.LockSurface();
			m.Finalize();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.UnlockSurface();
			m.Finalize();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.UnlockSurface();
			m.LockSurface();
			m.UnlockSurface();
			m.Finalize();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.UnlockSurface();
			m.UnlockSurface();
			m.Finalize();
		}));
	}

	SECTION("Manager throws when trying to update an unlocked surface")
	{
		SDL::SDLManager m {};

		REQUIRE_THROWS(std::invoke([&]()
		{
			m.Init({640, 480});
			m.UpdateSurface();
			m.Finalize();
		}));
	}

	SECTION("Manager allows to update an initialized surface")
	{
		SDL::SDLManager m {};

		REQUIRE_THROWS(std::invoke([&]()
		{
			m.LockSurface();
		}));
		REQUIRE_THROWS(std::invoke([&]()
		{
			m.UpdateSurface();
		}));
		REQUIRE_THROWS(std::invoke([&]()
		{
			m.UnlockSurface();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.UpdateSurface();
			m.UnlockSurface();
			m.Finalize();
		}));
	}

	SECTION("Manager allows to update pixels within an initialized surface")
	{
		SDL::SDLManager m {};

		REQUIRE_THROWS(std::invoke([&]()
		{
			m.PutPixel(0, 0, 0x000000);
		}));
		REQUIRE_THROWS(std::invoke([&]()
		{
			m.Init({640, 480});
			m.PutPixel(640, 0, 0x000000);
		}));
		REQUIRE_THROWS(std::invoke([&]()
		{
			m.Init({640, 480});
			m.PutPixel(0, 480, 0x000000);
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.PutPixel(0, 0, 0x000000);
			m.Finalize();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.LockSurface();
			m.PutPixel(0, 0, 0x000000);
			m.UnlockSurface();
			m.Finalize();
		}));
		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			m.PutPixel(0, 0, 0x000000);
			m.LockSurface();
			m.UpdateSurface();
			m.UnlockSurface();
			m.Finalize();
		}));
	}
}

TEST_CASE("Manager interface: event polling", "[SDL Wrapper]")
{
	SECTION("Manager allows to poll regular events")
	{
		SDL::SDLManager m {};

		REQUIRE_NOTHROW(std::invoke([&]()
		{
			m.Init({640, 480});
			const auto _ { m.PollSDLEvents() };
			m.Finalize();
		}));

		REQUIRE( std::invoke([&]()
		{
			m.Init({640, 480});
			const ProgramStatus event_status { m.PollSDLEvents() };
			return event_status == ProgramStatus::RUNNING;
		}));
	}

	// TO DO mock keyboard input
	/*
	SECTION("Manager allows to stop execution")
	{
		SDL::SDLManager m {};

		REQUIRE(std::invoke([&]()
		{
			m.Init({640, 480});
			return ProgramStatus::TERMINATE_OK == m.PollSDLEvents();
		}));
	}
	*/
}

