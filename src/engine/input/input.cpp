#include "input.h"

#include "definitions.h"
#include "sdl.h"

MoleDemo::InputManager::InputManager(SDL::SDLManager& manager):
	manager {manager}
{
}

mole_def::ProgramStatus MoleDemo::InputManager::PollEvents()
{
	return manager.PollSDLEvents();
}
