
#include<catch2/catch_test_macros.hpp>

#include <iostream>
#include <any>
#include <functional>
#include <type_traits>

import injection; 

struct test_class
{
	int value {};

	test_class()= default;
	virtual ~test_class()= default;
	test_class(const test_class&)= default;
	test_class(test_class&&)= default;
	test_class& operator=(const test_class&) = default;

	virtual int transform() { return 2; }
};

struct test_derived_class : public test_class
{
	using test_class::test_class;

	int transform() final override { return 3; }
};

TEST_CASE("Container instantiates", "[Injection]")
{
	REQUIRE_NOTHROW( MoleDemo::Container{} );
}

TEST_CASE("Container supports unique instances", "[Injection]")
{
	MoleDemo::Container c {};
	const auto int_functor { []{ return int{}; } };
	const auto test_functor { []{ return test_class{}; } };
	const auto test__derived_functor { []{ return test_derived_class{}; } };

	SECTION("binds unique instances")
	{
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<int>(); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class>(); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_derived_class>(); }));

		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<int, int>(); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class, test_class>(); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class, test_derived_class>(); }));

		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<int, int>( []{ return int{}; } ); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class, test_class>( []{ return test_class{}; } ); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class, test_derived_class>( []{ return test_derived_class{}; } ); }));

		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<int, int>( int_functor ); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class, test_class>( test_functor ); }));
		REQUIRE_NOTHROW( std::invoke( [&]{ c.BindUnique<test_class, test_derived_class>( test__derived_functor ); }));
	}

	SECTION("throws when asked to inject an unbinded type")
	{
		REQUIRE_THROWS( std::invoke( [&] { auto _ { c.Inject<int>() }; }));
		REQUIRE_THROWS( std::invoke( [&] { auto _ { c.Inject<test_class>() }; }));
		REQUIRE_THROWS( std::invoke( [&] { auto _ { c.Inject<test_derived_class>() }; }));
	}

	SECTION("Injects binded unique instances")
	{
		REQUIRE_NOTHROW( std::invoke([&]
		{
			c.BindUnique<int,int>();
			int& _ { c.Inject<int>() };
		}));

		 REQUIRE( std::invoke([&]
		 {
			const int value { 2 };
			c.BindUnique<int,int>([]{ return value; });
			int& instance { c.Inject<int>() };
			return instance = value;
		 }));
	}
}

TEST_CASE("Container supports unique instances WIP", "[Injection]")
{
	MoleDemo::Container c {};
	SECTION("WIP injection of binded unique instances")
	{
		 REQUIRE( std::invoke([&]
		 {
			const int value { 5 };
			c.BindUnique<int,int>([]{ return value; });
			int& a { c.Inject<int>() };
			int& b { c.Inject<int>() };
			++a;
			return a != b;
		 }));

		 REQUIRE( std::invoke([&]
		 {
			const int value { 5 };
			c.BindUnique<int,int>([]{ return value; });
			int& a { c.Inject<int>() };
			int& b { c.Inject<int>() };
			return a = 6;
		 }));
	}
}

/*
TEST_CASE("Container supports shared instances", "[Injection]")
{
	MoleDemo::Container c{};

	SECTION("binds shared instances")
	{
		REQUIRE_NOTHROW( std::invoke([&] { c.BindShared<int, int>(); }));
	}
}
 */

