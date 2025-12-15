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
    InputManager() = delete ("sdl dependency injection is required for the invariant");
    InputManager(SDL::SDLManager& manager);
    InputManager(const InputManager&) = delete ("a single instance is allowed, move it instead");
    InputManager(InputManager&&) = default;
    ~InputManager() = default;

    ProgramStatus PollEvents();
};
