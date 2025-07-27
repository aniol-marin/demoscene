module;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module imgui_wrapper;

import std;
import glfw_wrapper;

namespace mole::ui
{
    export struct UIContext
    {
        using io_t = decltype(ImGui::GetIO());

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        bool show_demo_window = true;
        bool show_another_window = false;

        UIContext() = delete;
        UIContext(mole::graphics::WindowContext& window);
        UIContext(const UIContext&&) = delete;
        UIContext(UIContext&&) = default;

        void RenderUI();
    };

    UIContext::UIContext(mole::graphics::WindowContext& window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        io_t context{ ImGui::GetIO() };
        context.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window.window, true);
        ImGui_ImplOpenGL3_Init();
    }

    void UIContext::RenderUI()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // demo
        static float f = 0.0f;

        ImGui::Begin("Mole Demoscene Editor [MOCK]");
        ImGui::Text("Hardcoded sandbox launch.");

        if (ImGui::Button(
                    "Launch"))
	{
		std::system("echo $PWD");
		std::system("./bin/sandbox");
	}

        io_t io{ ImGui::GetIO() };
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
