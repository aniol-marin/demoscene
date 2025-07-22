#include "glfw_wrapper.h"

#include <iostream>
#include <memory>

struct Context
{
    mole::graphics::WindowContext context{ { 640, 480 }, "MoleDemo Editor" };
    std::unique_ptr<mole::graphics::RenderContext> render;
    std::unique_ptr<mole::graphics::RenderContext> ui;
    Context()
    {
        render = std::make_unique<mole::graphics::RenderContext>(context);
        ui = std::make_unique<mole::ui::UIContext>(context);
        std::cout << "[MOCK] context initialization done\n";
    }

    void PollEvents() { context.PollEvents(); }

    void Draw() const { render->Render(); }

    void Present() { context.Swap(); }
};

int main()
{
    std::cout << "[MOCK] initializing editor\n";
    mole::graphics::Context context { {640, 480}, "MoleDemo Editor" };

    Context context;

    int frame{};
    const int max_frame{ 1000 };
    while (frame < max_frame)
    {
        context.PollEvents();
        context.Draw();
        ui.RenderUI();
        context.Present();
        ++frame;
        std::cout << std::right << std::setw(6) << frame << " / " << max_frame;
        std::flush(std::cout);
        std::cout << '\r';
        std::flush(std::cout);
    }

    std::cout << "[MOCK] editor closing\n";
}
