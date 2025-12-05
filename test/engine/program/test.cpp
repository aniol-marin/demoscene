#include <catch2/catch_test_macros.hpp>

#include <functional>
#include "engine.h"

SCENARIO("Program")
{
    GIVEN("a program")
    {
        WHEN("instantiated")
        {
            THEN("it must not throw")
            {
                REQUIRE_NOTHROW(MoleDemo::Program{Screen{640, 480}});
            }
            THEN("shouldn't be copyable")
            {
                CHECK(std::is_copy_constructible_v<MoleDemo::Program> == false);
            }
        }
        WHEN("put into use")
        {
            THEN("it should correctly fetch the status of the program")
            {
		CHECK(std::invoke([]()
		{
			auto p { MoleDemo::Program{Screen{640, 480}} };

			return p.Running() ;
		}));
            }
            THEN("it should correctly track the status of the program")
            {
		CHECK(std::invoke([]()
		{
			auto p { MoleDemo::Program{Screen{640, 480}} };
			p.SetStatus(ProgramStatus::TERMINATE_OK);

			return !p.Running() ;
		}));
            }
        }
    }
}
