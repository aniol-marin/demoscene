#include "demo.h"
#undef main

int main()
{
    MoleDemo::Demo demo("resources/project.xml");

    demo.Run();
}
