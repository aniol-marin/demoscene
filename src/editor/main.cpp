import editor_;
import std;

int main()
{
    Context context{};

    std::cout << "[EDITOR] running\n";
    while (context.is_active())
    {
        context.PollEvents();
        context.Draw();
    }

    std::cout << "[EDITOR] finalizing\n";
}
