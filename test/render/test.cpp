#include<catch2/catch_test_macros.hpp>

import std;
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

