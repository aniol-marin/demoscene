export module input;

import definitions;
export import sdl_wrapper;

namespace MoleDemo
{
	export struct InputManager;
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

