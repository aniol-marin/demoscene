import std;
import glfw_wrapper;
import glad_wrapper;
import imgui_wrapper;

class Context
{
    mole::graphics::WindowContext context;
    mole::graphics::RenderContext render;
    mole::ui::UIContext ui;

public:
    Context() : context{ { 640, 480 }, "MoleDemo Editor" }, render{ context }, ui{ context } {}

    void PollEvents() { context.PollEvents(); }

    void Draw()
    {
        render.Render();
        ui.RenderUI();
	context.Swap();
    }
};

int
main()
{
    Context context;

    int frame{};
    const int max_frame{ 1000 };
    while (frame < max_frame)
    {
        context.PollEvents();
        context.Draw();
        ++frame;
        std::cout << std::right << std::setw(6) << frame << " / " << max_frame;
        std::flush(std::cout);
        std::cout << '\r';
        std::flush(std::cout);
    }
}
