#include<catch2/catch_test_macros.hpp>

import std;
import timer;

SCENARIO("Timer")
{
	GIVEN("a timer")
	{
		WHEN("instantiated")
		{
			THEN("test suite should work")
			{
				CHECK(true);
			}
		}
	}
}

