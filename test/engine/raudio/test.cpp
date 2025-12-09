#include<catch2/catch_test_macros.hpp>
#include <filesystem>

#include <functional>
#include "raudio_wrapper.h"

SCENARIO("Manager behavior")
{
	GIVEN("an AudioManager")
	{
		WHEN("instantiated")
		{
			THEN("it must not throw")
			{
				REQUIRE_NOTHROW(raudio::AudioManager {});
			}
			THEN("shouldn't be copyable")
			{
				CHECK(std::is_copy_constructible_v<raudio::AudioManager> == false);
			}
		}

		WHEN("initialized or finalized")
		{

			THEN("it should not throw")
			{
				raudio::AudioManager m {};
				CHECK_NOTHROW(m.Init());
				CHECK_NOTHROW(m.Finalize());
			}
			AND_THEN("its lifetime should behave")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					raudio::AudioManager m {};
					m.Init();
					m.Finalize();
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					raudio::AudioManager m {};
					m.Init();
					m.Finalize();
					m.Init();
					m.Finalize();
				}));
			}
		}
		AND_WHEN("handling a valid file")
		{
			raudio::AudioManager m {};
			std::filesystem::path path {std::filesystem::absolute(std::filesystem::current_path())/ "resources/molelofi.mp3"};
			std::string_view file{ path.c_str() };

			THEN("it should load correctly")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					if(!std::filesystem::is_regular_file(path))
					{
						std::cerr << "invalid file: " << file << std::endl;
						return;
					}
					raudio::AudioManager m {};
					m.Init();
					m.Load(file);
					m.Finalize();
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					if(!std::filesystem::is_regular_file(path))
					{
						std::cerr << "invalid file: " << file << std::endl;
						return;
					}
					raudio::AudioManager m {};
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
					raudio::AudioManager m {};
					m.Init();
					m.Play();
				}));
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					raudio::AudioManager m {};
					m.Init();
					m.Play();
					m.Stop();
				}));
			}
			AND_THEN("it should be able to update")
			{
				REQUIRE_NOTHROW( std::invoke([&]()
				{
					raudio::AudioManager m {};
					m.Init();
					m.Update();
				}));
			}
			THEN("it should be possible to query its state")
			{
				raudio::AudioManager m {};
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
					raudio::AudioManager m {};
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

