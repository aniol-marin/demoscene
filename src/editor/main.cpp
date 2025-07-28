#include "editor.h"

#include <iostream>
#include <memory>

int main()
{
    Context context;

    std::cout << "[EDITOR] running\n";
    while (context.is_active())
    {
        context.PollEvents();
        context.Draw();
    }

    std::cout << "[EDITOR] finalizing\n";
}
