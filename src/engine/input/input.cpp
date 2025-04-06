module;

#include <iostream>

export module input;

import definitions;
import sdl;

namespace MoleDemo {

	export struct InputManager;
}

class MoleDemo::InputManager
{
	SDL::SDLManager manager{};
public:
	ProgramStatus PollEvents()
	{
		return manager.PollSDLEvents();
	}
};
