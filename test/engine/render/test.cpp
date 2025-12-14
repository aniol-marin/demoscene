#include<catch2/catch_test_macros.hpp>
#include <functional>

import render;

SCENARIO("Render")
{
	GIVEN("a renderer")
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

