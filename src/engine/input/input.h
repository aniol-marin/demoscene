#ifndef MOLE_INPUT
#define MOLE_INPUT

#include "definitions.h"
#include "sdl_wrapper.h"

namespace MoleDemo {

	struct InputManager;
}

using namespace mole_def;

class MoleDemo::InputManager
{
	SDL::SDLManager manager{};
public:
	ProgramStatus PollEvents();
};

#endif//! MOLE_INPUT

