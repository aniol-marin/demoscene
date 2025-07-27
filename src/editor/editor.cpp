export module editor;

import std;
import glfw_wrapper;
import glad_wrapper;
import imgui_wrapper;

export class Context
{
    mole::graphics::WindowContext context;
    mole::graphics::RenderContext render;
    mole::ui::UIContext ui;
    bool active{ true };

public:
    Context() : context{ { 640, 480 }, "MoleDemo Editor" }, render{ context }, ui{ context }
    {
        const char key = 0;
        context.AddCallback(key, [this] { active = false; });
    }
    Context(const Context&) = delete;
    Context(Context&&) = default;

    [[nodiscard]] bool is_active() { return active; }
    void PollEvents() { context.PollEvents(); }

    void Draw()
    {
        render.Render();
        ui.RenderUI();
        context.Swap();
    }
};
