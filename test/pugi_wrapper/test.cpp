#include<catch2/catch_test_macros.hpp>

import std;
import pugi_wrapper;

SCENARIO("Timer")
{
	GIVEN("a timer")
	{
		WHEN("instantiated")
		{
			THEN("test suite should work")
			{
				CHECK(true);
				REQUIRE_NOTHROW([]
				{
					Test();
				});
			}
		}
	}
}

