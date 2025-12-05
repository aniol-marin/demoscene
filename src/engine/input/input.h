#ifndef MOLE_INPUT
#define MOLE_INPUT

#include "definitions.h"
#include "sdl_wrapper.h"

namespace MoleDemo
{
	struct InputManager;
} // namespace MoleDemo

using namespace mole_def;

class MoleDemo::InputManager
{
	SDL::SDLManager& manager;

	public:

	InputManager() = delete;
	InputManager(SDL::SDLManager& manager);
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = default;
	~InputManager() = default;

	ProgramStatus PollEvents();
};

#endif //! MOLE_INPUT
