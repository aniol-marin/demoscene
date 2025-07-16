module;

extern "C" {
#define GLAD_IMPLEMENTATION
#include "glad/gl.h"
}

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
            const bool glLoaded{ 0 != gladLoadGL(window.address) };

            if (!glLoaded)
            {
                std::cerr << "OpenGL renderer failed to load";
                throw std::exception();
            }

            glDepthFunc(GL_LEQUAL);
            glEnable(GL_DEPTH_TEST);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
        }
        RenderContext(const RenderContext&) = delete;
        RenderContext(RenderContext&& tmp) : window{ tmp.window } {};
        ~RenderContext() = default;
    };
}
