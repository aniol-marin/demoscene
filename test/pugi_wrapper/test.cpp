#include<catch2/catch_test_macros.hpp>
#include "pugi.h"

import std;

SCENARIO("Usage of Pugi XML Library")
{
	GIVEN("the library")
	{
		WHEN("tested")
		{
			std::string path { std::filesystem::temp_directory_path() / "test.xml" };

			THEN("it should be possible to create temporary xml files")
			{
				REQUIRE_NOTHROW(std::invoke([&]
				{
					std::ofstream file {path};
					if (!file) throw std::exception{};
					if (!file.is_open()) throw std::exception{};

					file << "<test number=\"1\" word=\"hello\"/>\n";
					file.flush();
					file.close();
				}));
			}
			AND_THEN("it should be possible to load an xml file")
			{
				CHECK(std::invoke([&]
				{
					return mole::pugi_wrapper::Load(path);
				}));
				REQUIRE_NOTHROW(std::invoke([&]
				{
					mole::pugi_wrapper::node test{path};
					int v { test.get_number("number") };
					std::string w { test.get_text("word") };
				}));
				CHECK(std::string{ "hello" } == std::invoke([&]
				{
					mole::pugi_wrapper::node test{path};
					int v { test.get_number("number") };
					return test.get_text("word");
				}));
				CHECK(1 == std::invoke([&]
				{
					mole::pugi_wrapper::node test{path};
					return test.get_number("number");
				}));
			}
		}
	}
}

