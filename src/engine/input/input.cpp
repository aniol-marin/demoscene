export module input;

import std;
import definitions;
import sdl;

namespace MoleDemo {

	export struct InputManager;
}

class MoleDemo::InputManager
{
	SDL::SDLManager& manager;
public:
	InputManager() = delete;
	InputManager(SDL::SDLManager& manager) :
		manager{ manager }
	{
	}
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = default;

	ProgramStatus PollEvents()
	{
		return manager.PollSDLEvents();
	}
};
