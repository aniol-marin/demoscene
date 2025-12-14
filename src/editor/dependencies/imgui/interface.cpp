export module imgui_wrapper;

import glfw_wrapper;

namespace mole::ui
{
    export struct UIContext;
}

namespace mole::ui
{
    struct UIContext
    {
        bool show_demo_window = true;
        bool show_another_window = false;

        UIContext() = delete;
        UIContext(mole::graphics::WindowContext& window);
        UIContext(const UIContext&&) = delete;
        UIContext(UIContext&&) = default;

        void RenderUI();
    };
}
