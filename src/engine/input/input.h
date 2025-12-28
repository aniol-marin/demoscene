#ifndef MOLE_INPUT
#define MOLE_INPUT

#include <exception>
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
    InputManager(SDL::SDLManager& manager);
    ~InputManager() {}

    ProgramStatus PollEvents();
};

#endif //! MOLE_INPUT
