#include <iostream>

int main()
{
    std::cout << "[MOCK] initializing editor\n";
    /*
    mole::graphics::Context context { {640, 480}, "MoleDemo Editor" };
     */

    int c {};

    while ( c < 1000000)
    {
	    ++c;
	    std::cout << '.';
	    std::flush(std::cout);
    }

    std::cout << "[MOCK] editor closing\n";
}
