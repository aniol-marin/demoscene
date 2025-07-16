import std;
import glfw_wrapper;
import glad_wrapper;

struct Context
{
    mole::graphics::WindowContext context{ { 640, 480 }, "MoleDemo Editor" };
    std::unique_ptr<mole::graphics::RenderContext> render;
    Context()
    {
        std::cout << "[MOCK] context initializing\n";
        render = std::make_unique<mole::graphics::RenderContext>(context);
        std::cout << "[MOCK] context initialization done\n";
    }
};

int main()
{
    std::cout << "[MOCK] initializing editor\n";

    int c{};
    Context context;

    while (c < 100000)
    {
        ++c;
        std::cout << '.';
        std::flush(std::cout);
        std::cout << '\r';
        std::flush(std::cout);
    }
    std::cout << "\n";

    std::cout << "[MOCK] editor closing\n";
}
