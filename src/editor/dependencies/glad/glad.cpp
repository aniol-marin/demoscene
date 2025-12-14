module;

#define GLAD_IMPLEMENTATION
#include "glad/gl.h"
#include <iostream>
#include <vector>

module glad_wrapper;

namespace mole::graphics
{
    RenderContext::RenderContext(WindowContext& window) : window{ window }
    {
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

    RenderContext::RenderContext(RenderContext&& tmp) : window{ tmp.window } {};

    void RenderContext::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0, 1);
        for (const auto& r: drawCalls)
        {
            r.Draw();
        }
    }

    void RenderContext::Present() {}
}
