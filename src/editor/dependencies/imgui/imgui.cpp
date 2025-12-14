#include "imgui_wrapper.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

namespace mole::ui
{
    using io_t = decltype(ImGui::GetIO());
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
        using std::string_literals::operator""s;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // demo
        static float f = 0.0f;
        static int timeout = 2;

        ImGui::Begin("Mole Demoscene Editor [MOCK]");
        ImGui::Text("Hardcoded sandbox launch.");

        ImGui::InputInt("timeout", &timeout);
        if (ImGui::Button("Launch"))
        {
            std::system("echo 'launching $PWD/bin/sandbox'");
            std::system("./bin/sandbox");
        }

        if (ImGui::Button("Profile"))
        {
            std::system("echo 'profiling $PWD/bin/sandbox'");
            std::system(("valgrind ./bin/sandbox "s + std::to_string(timeout)).c_str());
        }

        io_t io{ ImGui::GetIO() };
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
