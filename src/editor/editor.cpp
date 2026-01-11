module;

#include <functional>
#include <typeinfo>

module editor_;

import glfw_wrapper;
import glad_wrapper;
import imgui_wrapper;

namespace mole::editor
{
    Context::Context() : context{ { 640, 480 }, "MoleDemo Editor" }, render{ context }, ui{ context }
    {
        const char key = 0;
        context.AddCallback(key, [this] { active = false; });
    }

    [[nodiscard]] bool Context::is_active()
    {
        return active;
    }
    void Context::PollEvents()
    {
        context.PollEvents();
    }

    void Context::Draw()
    {
        render.Render();
        ui.RenderUI();
        context.Swap();
    }
}
