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
        bool show_demo_window = true;
        bool show_another_window = false;

        UIContext() = delete ("dependency injection is required for the invariant");
        UIContext(mole::graphics::WindowContext& window);
        UIContext(const UIContext&&) = delete ("a single instance is allowed, move it instead");
        UIContext(UIContext&&) = default;

        void RenderUI();
    };
}
