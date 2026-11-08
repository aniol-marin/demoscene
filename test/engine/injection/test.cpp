#include<catch2/catch_test_macros.hpp>

#include <functional>
#include "injection.h"

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

TEST_CASE("Container itself behaves as expected", "[Injection]")
{
	SECTION("container can be instantiated")
	{
		REQUIRE_NOTHROW( MoleDemo::Container{} );
	}

	SECTION("throws when asked to inject an unbinded type")
	{
		MoleDemo::Container c {};

		REQUIRE_THROWS( c.Inject<int>() );
		REQUIRE_THROWS( c.Inject<test_class>() );
		REQUIRE_THROWS( c.Inject<test_derived_class>() );
	}
}

TEST_CASE("Container supports unique instances", "[Injection]")
{
	MoleDemo::Container c {};
	const auto int_functor { [](){ return new int{}; } };
	const auto test_functor { [](){ return new test_class{}; } };
	const auto test_derived_functor { [](){ return new test_derived_class{}; } };

	/*
	SECTION("binds unique instances")
	{
		REQUIRE_NOTHROW( [&](){ c.BindUnique<int>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_derived_class>(); }());

		REQUIRE_NOTHROW( [&](){ c.BindUnique<int, int>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class, test_class>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class, test_derived_class>(); }());

		REQUIRE_NOTHROW( [&](){ c.BindUnique<int, int>( [](){ return new int{}; } ); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class, test_class>( [](){ return new test_class{}; } ); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class, test_derived_class>( [](){ return new test_derived_class{}; } ); }());

		REQUIRE_NOTHROW( [&](){ c.BindUnique<int, int>( int_functor ); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class, test_class>( test_functor ); }());
		REQUIRE_NOTHROW( [&](){ c.BindUnique<test_class, test_derived_class>( test_derived_functor ); }());
	}

	SECTION("Injects binded unique instances")
	{
		REQUIRE_NOTHROW( [&]()
		{
			c.BindUnique<int>();
			int& _ { c.Inject<int>() };
		}());

		 REQUIRE( [&]()
		 {
			const int value { 2 };
			c.BindUnique<int>([&](){ return new int{value}; });
			int& instance { c.Inject<int>() };
			return instance == value;
		 }());

		 REQUIRE( [&]()
		 {
			const int value { 5 };
			c.BindUnique<int>([&](){ return new int{value}; });
			int& a { c.Inject<int>() };
			int& b { c.Inject<int>() };
			++a;
			return a != b;
		 }());

		 REQUIRE( [&]()
		 {
			const int value { 5 };
			c.BindUnique<int>([value](){ return new int{value}; });
			int& a { c.Inject<int>() };
			int& b { c.Inject<int>() };
			++a;
			return a == (value + 1) && b == value;
		 }());
	}

	SECTION("Supports polymorphism")
	{
		REQUIRE( [&]()
		{
			c.BindUnique<test_class, test_class>();

			test_class& a { c.Inject<test_class>() };
			test_class b { };

			return a.transform() == b.transform();
		}());

		REQUIRE( [&]()
		{
			c.BindUnique<test_derived_class>();

			test_class& a { c.Inject<test_derived_class>() };
			test_derived_class b { };

			return a.transform() == b.transform();
		}());

		REQUIRE( [&]()
		{
			c.BindUnique<test_class, test_derived_class>();
			test_class& a { c.Inject<test_class>() };
			test_derived_class b { };
			return a.transform() == b.transform();
		}());

		REQUIRE( [&]()
		{
			c.BindUnique<test_class, test_derived_class>();
			c.BindUnique<test_derived_class>();

			test_class& a { c.Inject<test_class>() };
			test_class& b { c.Inject<test_derived_class>() };

			return a.transform() == b.transform();
		}());
	}
	*/
}

/*
TEST_CASE("Container supports shared instances", "[Injection]")
{
	MoleDemo::Container c {};
	const auto int_functor { [](){ return new int{}; } };
	const auto test_functor { [](){ return new test_class{}; } };
	const auto test_derived_functor { [](){ return new test_derived_class{}; } };

	SECTION("binds shared instances")
	{
		REQUIRE_NOTHROW( [&](){ c.BindShared<int>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_derived_class>(); }());

		REQUIRE_NOTHROW( [&](){ c.BindShared<int, int>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class, test_class>(); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class, test_derived_class>(); }());

		REQUIRE_NOTHROW( [&](){ c.BindShared<int, int>( [](){ return new int{}; } ); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class, test_class>( [](){ return new test_class{}; } ); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class, test_derived_class>( [](){ return new test_derived_class{}; } ); }());

		REQUIRE_NOTHROW( [&](){ c.BindShared<int, int>( int_functor ); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class, test_class>( test_functor ); }());
		REQUIRE_NOTHROW( [&](){ c.BindShared<test_class, test_derived_class>( test_derived_functor ); }());
	}

	SECTION("Injects binded shared instances")
	{
		REQUIRE_NOTHROW( [&]()
		{
			c.BindShared<int>();
			int& _ { c.Inject<int>() };
		}());

		 REQUIRE( [&]()
		 {
			const int value { 2 };
			c.BindUnique<int>([&](){ return new int{value}; });
			int& instance { c.Inject<int>() };
			return instance = value;
		 }());

		 REQUIRE( [&]()
		 {
			const int value { 5 };
			c.BindUnique<int>([&](){ return new int{value}; });
			int& a { c.Inject<int>() };
			int& b { c.Inject<int>() };
			++a;
			return a == b;
		 }());

		 REQUIRE( [&]()
		 {
			const int value { 5 };
			c.BindUnique<int>([&](){ return new int{value}; });
				int& a { c.Inject<int>() };
				int& b { c.Inject<int>() };
				++a;
				return a == 6 && b == a;
		 }());
	}
}

 */
