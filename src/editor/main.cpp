import std;
import glfw_wrapper;
import glad_wrapper;
import imgui_wrapper;

struct Context
{
    mole::graphics::WindowContext context{ { 640, 480 }, "MoleDemo Editor" };
    std::unique_ptr<mole::graphics::RenderContext> render;
    Context()
    {
        render = std::make_unique<mole::graphics::RenderContext>(context);
        std::cout << "[MOCK] context initialization done\n";
    }

    void PollEvents() { context.PollEvents(); }

    void Draw() const
    {
        render->Render();
        context.Swap();
    }
};

int main()
{
    std::cout << "[MOCK] initializing editor\n";

    Context context;
    mole::ui::initialize(context.context);

    int frame{};
    const int max_frame{ 1000 };
    while (frame < max_frame)
    {
        context.PollEvents();
        context.Draw();
	mole::ui::RenderUI();
        ++frame;
        std::cout << std::right << std::setw(6) << frame << " / " << max_frame;
        std::flush(std::cout);
        std::cout << '\r';
        std::flush(std::cout);
    }
    std::cout << "\n";

    std::cout << "[MOCK] editor closing\n";
}
