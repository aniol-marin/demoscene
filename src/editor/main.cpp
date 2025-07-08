import std;
import glfw_wrapper;
import glad_wrapper;

struct Context
{
    mole::graphics::Context context{ { 640, 480 }, "MoleDemo Editor" };
};

int main()
{
    std::cout << "[MOCK] initializing editor\n";

    int c{};
    Context context;

    while (c < 1000000)
    {
        ++c;
        std::cout << '.';
        std::flush(std::cout);
    }
    std::cout << "\n";
    std::cout << mole::graphics::test() << "\n";

    std::cout << "[MOCK] editor closing\n";
}
