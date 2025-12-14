#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <filesystem>
#include <string>
#include <fstream>

import serialization;

using tree = mole::pugi_wrapper::tree;
using node = mole::pugi_wrapper::generic_node;

std::filesystem::path path { std::filesystem::temp_directory_path() / "test.xml" };

/*
struct unspecialized{};
struct specialized{};
struct custom
{
	int number{};
	std::string word{};
};
struct nested_custom
{
	std::vector<custom> data{};
};

template<>
struct mole::pugi_wrapper::node<specialized> : mole::pugi_wrapper::generic_node
{
	node() : generic_node{}
	{
	}
	node(const pugi::xml_node&)
		: generic_node{}
	{
	}
	node(const generic_node&)
		: generic_node{}
	{
	}
	node(const node&) = delete;
	node(const node&&) = delete;
	~node() override = default;
};

template<>
struct mole::pugi_wrapper::node<custom> : mole::pugi_wrapper::generic_node
{
	custom data{};

	node() : generic_node{}
	{
	}
	node(const pugi::xml_node& node)
		: generic_node{}
	{
		mole::pugi_wrapper::generic_node content { "child", node };
		data.number = { content.get_number( "number" ) };
		data.word = { content.get_text( "word" ) };
	}
	node(const generic_node&)
		: generic_node{}
	{
	}
	node(const node&) = delete;
	node(const node&&) = delete;
	~node() override = default;

	const custom& deserialize() const
	{
		return data;
	}
};

template<>
struct mole::pugi_wrapper::node<nested_custom> : mole::pugi_wrapper::generic_node
{
	nested_custom data{};

	node() : generic_node{}
	{
	}
	node(const pugi::xml_node& node)
		: generic_node{}
	{
		mole::pugi_wrapper::generic_node content { "test", node };
		const auto& children { content.get_children("child") };
		for(const auto& child : children)
		{
			specialized_node<custom> nested { child.node };
			data.data.emplace_back( nested.deserialize() );
		}
	}
	node(const generic_node& other)
		: generic_node{}
	{
	}
	node(const node&) = delete;
	node(const node&&) = delete;
	~node() override = default;

	const nested_custom& deserialize() const
	{
		return data;
	}
};
 */

void replace_content(std::filesystem::path file_path, std::string content)
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
					node  node{test.get_root_node("test")};
				}));
			}
			AND_THEN("it should be possible to read attributes")
			{
				replace_content(path, "<test t='55' number=\"1\" word=\"hello\"/>\n");

				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node node{test.get_root_node("test")};
					int v { node.get_number("number") };
				}));

				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node node{test.get_root_node("test")};
					std::string w { node.get_text("word") };
				}));

				CHECK(std::string{ "hello" } == std::invoke([&]
				{
					tree test{path};
					node node{test.get_root_node("test")};
					return node.get_text("word");
				}));

				CHECK(1 == std::invoke([&]
				{
					tree test{path};
					node node{test.get_root_node("test")};
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
					node parent{ test.get_root_node("test") };
					node child { parent.get_child("child") };
				}));
				REQUIRE_NOTHROW(std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					std::vector<node> children {  parent.get_children("child") };
				}));
				CHECK(2 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.size();
				}));
				CHECK(1 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					node child { parent.get_child("child") };
					return child.get_number("number");
				}));
				CHECK(1 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.front().get_number("number");
				}));
				CHECK(2 == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.back().get_number("number");
				}));
				CHECK(std::string { "hello" }  == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.front().get_text("word");
				}));
				CHECK(std::string { "world" } == std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					std::vector<node> children {  parent.get_children("child") };
					return children.back().get_text("word");
				}));
			}
		}
		/*
		WHEN("a specialization doesn't exist")
		{
			THEN("it should not work")
			{
				CHECK(true);
				CHECK_THROWS( std::invoke([]
				{
					specialized_node<unspecialized>();
				}));
				CHECK_THROWS( std::invoke([]
				{
					tree test{path};
					node node{ test.get_root_node("test") };
					specialized_node<unspecialized> unspecialized { node };
				}));
				CHECK_THROWS( std::invoke([]
				{
					pugi::xml_document document {};
					pugi::xml_node node {  document.child("child") };
					specialized_node<unspecialized> unspecialized { node };
				}));
			}
		}
		WHEN("a specialization exists")
		{
			THEN("it should work")
			{
				CHECK(true);
				CHECK_NOTHROW( std::invoke([]
				{
					specialized_node<specialized>();
				}));
				CHECK_NOTHROW( std::invoke([]
				{
					tree test{path};
					node node{ test.get_root_node("test") };
					specialized_node<specialized> specialized { node };
				}));
				CHECK_NOTHROW( std::invoke([]
				{
					pugi::xml_document document {};
					pugi::xml_node node {  document.child("child") };
					specialized_node<specialized> specialized { node };
				}));
			}
			AND_THEN("should be able to parse custom structures")
			{
				REQUIRE_NOTHROW( std::invoke([]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					specialized_node<custom> custom { parent.get_child("child").node };
				}));
				CHECK(std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					specialized_node<custom> child { parent.get_child("child").node };
					custom deserialized { child.deserialize() };

					return true
						&& deserialized.number == 1
						&& deserialized.word.compare("hello") == 0;
				}));
			}
			AND_THEN("should be able to parse nested structures")
			{
				REQUIRE_NOTHROW( std::invoke([]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					specialized_node<nested_custom> custom { parent.node };
				}));
				CHECK(std::invoke([&]
				{
					tree test{path};
					node parent{ test.get_root_node("test") };
					specialized_node<nested_custom> custom { parent.node };
					nested_custom deserialized { custom.deserialize() };

					return true
						&& deserialized.data.front().number == 1
						&& deserialized.data.front().word.compare("hello") == 0
						&& deserialized.data.back().number == 2
						&& deserialized.data.back().word.compare("world") == 0;
				}));
			}
		}
 */
	}
}

SCENARIO("Serializing with Pugi XML Library")
{
	//TO DO
	CHECK(true);
}

