#include<catch2/catch_test_macros.hpp>
#include "pugi.h"

import std;

std::string path { std::filesystem::temp_directory_path() / "test.xml" };

void replace_content(std::string file_path, std::string content)
{
	std::ofstream file {};
	file.open(file_path, std::ofstream::out | std::ofstream::trunc);
	if (!file) throw std::exception{};
	if (!file.is_open()) throw std::exception{};

	file << content;
	file.flush();
	file.close();
}

TEST_CASE("Test-exclusive dependencies before serialization", "[XML]")
{
	SECTION("Temporary file exists")
	{
		REQUIRE_NOTHROW(std::invoke([&]
		{
			std::ofstream file {path};
			if (!file) throw std::exception{};
			if (!file.is_open()) throw std::exception{};
			file.close();
		}));
	}
	
	SECTION("Temporary file can be modified")
	{
		REQUIRE_NOTHROW(std::invoke([&]
		{
			replace_content(path, "Hello, World!\n");
		}));
	}
}

SCENARIO("Parsing with Pugi XML Library")
{
	GIVEN("the library")
	{
		WHEN("tested")
		{
			THEN("it should be possible to load an xml file")
			{
				replace_content(path, "<test/>\n");
				REQUIRE_NOTHROW(std::invoke([&]
				{
					mole::pugi_wrapper::tree test{path};
				}));

				replace_content(path, "<test number=\"1\" word=\"hello\"/>\n");
				REQUIRE_NOTHROW(std::invoke([&]
				{
					mole::pugi_wrapper::tree test{path};
					int v { test.get_number("number") };
					std::string w { test.get_text("word") };
				}));
				CHECK(std::string{ "hello" } == std::invoke([&]
				{
					mole::pugi_wrapper::tree test{path};
					int v { test.get_number("number") };
					return test.get_text("word");
				}));
				CHECK(1 == std::invoke([&]
				{
					mole::pugi_wrapper::tree test{path};
					return test.get_number("number");
				}));
			}
		}
	}
}

SCENARIO("Serializing with Pugi XML Library")
{
	//TO DO
	CHECK(true);
}
