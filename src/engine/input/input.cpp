#include "input.h"

namespace MoleDemo
{
	MoleDemo::InputManager::InputManager(SDL::SDLManager& manager) : manager{ manager } {}

	mole_def::ProgramStatus MoleDemo::InputManager::PollEvents()
	{
		return manager.PollSDLEvents();
	}
}
