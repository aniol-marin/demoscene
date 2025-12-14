#include <catch2/catch_test_macros.hpp>
#include <type_traits>
#include <functional>
#include <iostream>
#include <thread>

import timer;

SCENARIO("Timer")
{
    GIVEN("a timer")
    {
        WHEN("instantiated")
        {
            THEN("it must not throw")
            {
                REQUIRE_NOTHROW(MoleDemo::Timer{});
            }
            THEN("shouldn't be copyable")
            {
                CHECK(std::is_copy_constructible_v<MoleDemo::Timer> == false);
            }
        }
        WHEN("put into use")
        {
            THEN("it should measure time accurately")
            {
		CHECK(std::invoke([]()
		{
			MoleDemo::Timer t{};
			int initial { t. GetTime() };
			std::cerr << "\n initial: [" << initial << "]";
			std::cerr << "\n sleeping...";
			std::this_thread::sleep_for(std::chrono::seconds{1});
			t.WaitUntilNextFrame();
			int final { t. GetTime() };
			std::cerr << "\n final: [" << final << "]";
			return final == initial + 1;
		}));
            }
        }
    }
}
