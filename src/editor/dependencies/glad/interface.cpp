module;

#define GLAD_IMPLEMENTATION
#include <vector>
#include "glad/gl.h"

export module glad_wrapper;

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
        RenderContext(WindowContext& window);
        RenderContext(const RenderContext&) = delete;
        RenderContext(RenderContext&& tmp);
        ~RenderContext() = default;

        void Render();
        void Present();
    };
}
