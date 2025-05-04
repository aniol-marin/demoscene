#include<catch2/catch_test_macros.hpp>
#include "pugi.h"

import std;

using tree = mole::pugi_wrapper::tree;
using node = mole::pugi_wrapper::generic_node;

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
					tree test{path};
				}));

				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node  node{test.get_generic_node("test")};
				}));
			}
			AND_THEN("it should be possible to read attributes")
			{
				replace_content(path, "<test t='55' number=\"1\" word=\"hello\"/>\n");

				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node node{test.get_generic_node("test")};
					int v { node.get_number("number") };
				}));

				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node node{test.get_generic_node("test")};
					std::string w { node.get_text("word") };
				}));

				CHECK(std::string{ "hello" } == std::invoke([&]
				{
					tree test{path};
					node node{test.get_generic_node("test")};
					return node.get_text("word");
				}));

				CHECK(1 == std::invoke([&]
				{
					tree test{path};
					node node{test.get_generic_node("test")};
					return node.get_number("number");
				}));
			}
			AND_THEN("it should be possible to fetch attributes from children nodes")
			{
				replace_content(
					path,
					"<test>\n"
					"   <child number=\"1\" word=\"hello\"/>\n"
					"   <child number=\"2\" word=\"world\"/>\n"
					"</test>\n"
				);

				CHECK(true);
				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					node child { parent.get_child("child") };
				}));
				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					std::vector<node> children {  parent.get_children("child") };
				}));
				CHECK(2 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.size();
				}));
				CHECK(1 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					node child { parent.get_child("child") };
					return child.get_number("number");
				}));
				CHECK(1 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.front().get_number("number");
				}));
				CHECK(2 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.back().get_number("number");
				}));
				CHECK(std::string { "hello" }  == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.front().get_text("word");
				}));
				CHECK(std::string { "world" } == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_generic_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.back().get_text("word");
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
