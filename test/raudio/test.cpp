#include<catch2/catch_test_macros.hpp>

import std;
import raudio;
import definitions;

SCENARIO("Manager behavior")
{
	GIVEN("an AudioManager")
	{
		WHEN("instantiated")
		{
			THEN("it must not throw")
			{
				REQUIRE_NOTHROW(RAudio::AudioManager {});
			}
			THEN("shouldn't be copyable")
			{
				CHECK(std::is_copy_constructible_v<RAudio::AudioManager> == false);
			}
		}

		WHEN("initialized or finalized")
		{

			THEN("it should not throw")
			{
				RAudio::AudioManager m {};
				CHECK_NOTHROW(m.Init());
				CHECK_NOTHROW(m.Finalize());
			}
			AND_THEN("its lifetime should behave")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Finalize();
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Finalize();
					m.Init();
					m.Finalize();
				}));
			}
		}
		AND_WHEN("handling a valid file")
		{
			RAudio::AudioManager m {};
			std::string_view file{ "/home/bru/demoscene-2023/resources/molelofi.mp3" };

			THEN("it should load correctly")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Load(file);
					m.Finalize();
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Load(file);
					m.Unload();
					m.Finalize();
				}));
			}
			AND_THEN("it should be able to handle play cycles")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Play();
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Play();
					m.Stop();
				}));
			}
			AND_THEN("it should be able to update")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Tick();
				}));
			}
			THEN("it should be possible to query its state")
			{
				RAudio::AudioManager m {};
				CHECK_NOTHROW( m.GetIntensity() );
				CHECK_NOTHROW( m.GetDuration() );
			}
		}

	}
	AND_GIVEN("a misused AudioManager")
	{
		WHEN("doubly initialized")
		{
			THEN("it should throw")
			{
				CHECK_THROWS( std::invoke([&]()
				{
					RAudio::AudioManager m {};
					m.Init();
					m.Init();
				}));
			}
		}
		WHEN("not initialized")
		{
			THEN("shouldn't accept asset loading")
			{
				REQUIRE(true);
			}
		}
	}
}

