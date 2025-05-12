#include "input.h"

#include "sdl_wrapper.h"

namespace MoleDemo {

	struct InputManager;
}

using namespace mole_def;

ProgramStatus MoleDemo::InputManager::PollEvents()
{
	return manager.PollSDLEvents();
}
