#include <catch2/catch_test_macros.hpp>

#include "GLFW/glfw3.h"

SCENARIO("Compilation")
{
    GIVEN("the inclusion of the GLFW header")
    {
        WHEN("compiled")
        {
            THEN("it must compile")
            {
                CHECK(true);
            }
        }
    }
}
