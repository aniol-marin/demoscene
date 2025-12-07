module input;

import definitions;
import sdl_wrapper;

MoleDemo::InputManager::InputManager(SDL::SDLManager& manager) : manager{ manager } {}

mole_def::ProgramStatus
MoleDemo::InputManager::PollEvents()
{
    return manager.PollSDLEvents();
}
