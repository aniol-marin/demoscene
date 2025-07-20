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
    struct DrawCall
    {
        /*
            GladDrawCall(asset emmiter, RenderableType type, Shader& shader, Mesh& mesh, Textures textures, Camera&
           camera, Transform* transform, Callback update);
        */
        DrawCall() = default;
        ~DrawCall() = default;
        void Draw() const {}

    private:
        /*
            static unsigned int nextId;
            unsigned int id;
            VAO vao;
            VBO vbo;
            EBO ebo;
            Shader& shader;
            Mesh& mesh;
            Camera& camera;
            Textures textures;
            Transform* transform;
            Callback update;
            */
    };

    export struct RenderContext
    {

        WindowContext& window;
        std::vector<DrawCall> drawCalls;

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

        void Render()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            /*
	       glClearColor(0.1, 0.1, 0, 1);
	       for (const auto& r: drawCalls)
	       {
	       r.Draw();
	       }
       */
        }

	void Present()
	{
	}
    };
}
