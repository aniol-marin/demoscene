import editor;

import std;

int main()
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
