#include<catch2/catch_test_macros.hpp>

import std;
import raudio;
import definitions;

TEST_CASE("Raylib Audio Tests", "[RAudio Wrapper]")
{
	SECTION("test suite works")
	{
		REQUIRE(true);
	}
}

SCENARIO("Asset load simulation", "[RAudio Wrapper]")
{
	GIVEN("an AudioManager")
	{
		WHEN("instantiated")
		{
			THEN("it should not throw")
			{
				REQUIRE(true);
			}
		}
	}
	AND_GIVEN("a misused AudioManager")
	{
		WHEN("doubly initialized")
		{
			THEN("it should throw")
			{
				REQUIRE(true);
			}
			AND_THEN("it should be still possible to initialize")
			{
				REQUIRE(true);
			}
		}
		AND_WHEN("not initialized")
		{
			THEN("shouldn't accept asset loading")
			{
				REQUIRE(true);
			}
		}
	}
}

TEST_CASE("Manager basic behavior", "[RAudio Wrapper]")
{
	SECTION("Manager can be instantiated")
	{
		REQUIRE_NOTHROW(RAudio::AudioManager{});
	}

	SECTION("RAudio can be started and stopped")
	{
		RAudio::AudioManager m {};

		REQUIRE_NOTHROW( m.Init() );
		REQUIRE_NOTHROW( m.Finalize() );
		REQUIRE_NOTHROW( std::invoke([&]()
		{
			m.Init();
			m.Finalize();
		}));
		REQUIRE_THROWS( std::invoke([&]()
		{
			m.Init();
			m.Init();
		}));
	}

	SECTION("Interface mock")
	{
		RAudio::AudioManager m {};

		REQUIRE_NOTHROW( m.Load("/home/bru/demoscene-2023/resources/molelofi.mp3") );
		REQUIRE_NOTHROW( m.Unload() );
		REQUIRE_NOTHROW( m.Play() );
		REQUIRE_NOTHROW( m.Stop() );
		REQUIRE_NOTHROW( m.Tick() );
		REQUIRE_NOTHROW( 1 == m.GetDuration() );
		REQUIRE_NOTHROW( 1 == m.GetIntensity() );
	}
}

/*
TEST_CASE("Manager interface: surface interaction", "[RAudio Wrapper]")
{
	SECTION("Surface can be locked and ulocked without restrictions")
	{
		RAudio::SDLManager m {};

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
		RAudio::SDLManager m {};

		REQUIRE_THROWS(std::invoke([&]()
		{
			m.Init({640, 480});
			m.UpdateSurface();
			m.Finalize();
		}));
	}

	SECTION("Manager allows to update an initialized surface")
	{
		RAudio::SDLManager m {};

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
		RAudio::SDLManager m {};

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

TEST_CASE("Manager interface: event polling", "[RAudio Wrapper]")
{
	SECTION("Manager allows to poll regular events")
	{
		RAudio::SDLManager m {};

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
}
 */

