export module glad_wrapper;

import std;
import glfw_wrapper;

namespace mole::graphics
{
    export struct RenderContext
    {

        WindowContext& window;

        RenderContext() = delete;
        RenderContext(WindowContext& window) : window{ window }
        {
            std::cout << "[MOCK] render initializing\n";
            std::cout << "[MOCK] received context is" << window.name << "\n";
        }
        RenderContext(const RenderContext&) = delete;
        RenderContext(RenderContext&& tmp) : window{ tmp.window } {};
        ~RenderContext() = default;
    };
}
