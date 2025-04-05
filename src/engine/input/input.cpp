module;

#include "sdl.h"
#include <iostream>

export module input;

import definitions;
/*
import sdl;
*/

namespace MoleDemo {

	export struct InputManager;
}

class MoleDemo::InputManager
{
	/*
	SDL::SDLManager manager{};
	*/
public:
	ProgramStatus PollEvents()
	{
		std::cout << "polling disabled\n";
		return ProgramStatus::RUNNING;
		/*
		return manager.PollSDLEvents();
		*/
	}
};
