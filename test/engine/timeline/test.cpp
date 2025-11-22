#include <catch2/catch_test_macros.hpp>

import std;
import timeline;

SCENARIO("Timeline")
{
	GIVEN("a timeline")
	{
		WHEN("instantiated")
		{
			THEN("unit tests should run")
			{
				CHECK(true);
			}
			AND THEN("unit tests should be written")
			{
				CHECK(false);
			}
		}));
            }
        }
    }
}
