#include<catch2/catch_test_macros.hpp>

import std;
import timer;

SCENARIO("Timeline")
{
	GIVEN("a timeline")
	{
		WHEN("instantiated")
		{
			MoleDemo::Timer t{};
			int initial { t. GetTime() };
			std::cerr << "\n initial: [" << initial << "]";
			std::cerr << "\n sleeping...";
			std::this_thread::sleep_for(std::chrono::seconds{1});
			t.WaitUntilNextFrame();
			int final { t. GetTime() };
			std::cerr << "\n final: [" << final << "]";
			return final == initial + 1;
		}));
            }
        }
    }
}
