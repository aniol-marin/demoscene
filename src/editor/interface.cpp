export module editor_;

import std;
import glfw_wrapper;
import glad_wrapper;
import imgui_wrapper;

namespace mole::editor
{
    export class Context;
}

namespace mole::editor
{
    class Context
    {
        mole::graphics::WindowContext context;
        mole::graphics::RenderContext render;
        mole::ui::UIContext ui;
        bool active{ true };

    public:
        Context();
        Context(const Context&) = delete ("a single instance is allowed, move it instead");
        Context(Context&&) = default;

        [[nodiscard]] bool is_active();
        void PollEvents();

        void Draw();
    };
}
