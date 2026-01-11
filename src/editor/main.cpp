#include "editor.h"

#include <iostream>

int main()
{
    mole::editor::Context context{};

    std::cout << "[EDITOR] running\n";
    while (context.is_active())
    {
        context.PollEvents();
        context.Draw();
    }

    std::cout << "[EDITOR] finalizing\n";
}
