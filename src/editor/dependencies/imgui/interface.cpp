module;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module imgui_wrapper;

import std;
import glfw_wrapper;

namespace mole::ui
{
    export struct UIContext;
}

namespace mole::ui
{
    struct UIContext
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
}
