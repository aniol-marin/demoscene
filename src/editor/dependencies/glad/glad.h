#ifndef MOLE_GLAD_WRAPPER_H
#define MOLE_GLAD_WRAPPER_H

#include "glfw_wrapper.h"

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

    struct RenderContext
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

#endif

