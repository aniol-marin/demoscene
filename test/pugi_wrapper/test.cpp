#include<catch2/catch_test_macros.hpp>

import std;
import pugi_wrapper;

SCENARIO("Usage of Pugi XML Library")
{
	GIVEN("the library")
	{
		WHEN("tested")
		{
			std::string path { std::filesystem::temp_directory_path() / "test.xml" };

			THEN("test suite should work")
			{
				REQUIRE_NOTHROW(Mock());
			}
			AND_THEN("it should be possible to create temporary xml files")
			{
				REQUIRE_NOTHROW(std::invoke([&]
				{
					std::ofstream file {path};
					if (!file) throw std::exception{};
					if (!file.is_open()) throw std::exception{};

					file << "<test/>\n";
					file.flush();
					file.close();
				}));
			}
			AND_THEN("it should be possible to load an xml file")
			{
				CHECK(std::invoke([&]
				{
					return Load(path);
				}));
			}
		}
	}
}

