module;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module imgui_wrapper;

import std;

namespace mole::ui
{
    struct UIContext
    {
        using io_t = decltype(ImGui::GetIO());
        io_t io;

        UIContext() = delete;
        UIContext(io_t io) : io{ io } {}
    };

    UIContext* context{};
    export void initialize()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        /*
     [[maybe_unused]] ImGuiIO& io = ImGui::GetIO();
     */
        context = new UIContext{ ImGui::GetIO() };
        context->io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        /*
                EMSCRIPTEN_MAINLOOP_BEGIN
        */
        /*loop here*/
    }

    export void RenderUI()
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        /*end loop*/

        // demo
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
/*
        ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*) &clear_color); // Edit 3 floats representing a color
	*/

        if (ImGui::Button(
                    "Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        auto& io{ context->io };
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
}
