#include "glad.h"
#include "glfw_wrapper.h"
#include "imgui_wrapper.h"

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
        Context(const Context&) = delete;
        Context(Context&&) = default;

        [[nodiscard]] bool is_active();
        void PollEvents();

        void Draw();
    };
}
