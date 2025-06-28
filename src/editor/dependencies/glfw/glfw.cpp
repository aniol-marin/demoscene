export module glfw_wrapper;

import std;

namespace mole::graphics
{
    struct Context
    {
    };

    export Context create_context()
    {
        std::cout << "[MOCK] create context\n";
        return {};
    }
}
