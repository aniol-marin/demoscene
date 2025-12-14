#ifndef MOLE_IMGUI_WRAPPER_H
#define MOLE_IMGUI_WRAPPER_H

#include "glfw_wrapper.h"

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

#endif
